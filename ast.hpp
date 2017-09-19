#ifndef __AST_HPP__
#define __AST_HPP__ 1

#include <string>
#include <vector>
using namespace std;

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Transforms/Scalar.h"

#define OPTIMIZE 0

using namespace llvm;
using namespace llvm::legacy;

class ExprAST {
public:
  virtual ~ExprAST();
  virtual Value *codegen() const = 0;
  int tip;
};

class NumberDExprAST : public ExprAST {
public:
  NumberDExprAST(double v) : Val(v) {}
  Value *codegen() const;

private:
  double Val;
};

class NumberIExprAST : public ExprAST {
public:
  NumberIExprAST(int v) : Val(v) {}
  Value *codegen() const;

private:
  int Val;
};

class VariableExprAST : public ExprAST {
public:
  VariableExprAST(string s) : Name(s) {}
  Value *codegen() const;

private:
  string Name;
};

class InnerExprAST : public ExprAST {
public:
  InnerExprAST(ExprAST *a);
  InnerExprAST(ExprAST *a, ExprAST *b);
  InnerExprAST(ExprAST *a, ExprAST *b, ExprAST *c);
  InnerExprAST(ExprAST *a, ExprAST *b, ExprAST *c, ExprAST *d);
  InnerExprAST(vector<ExprAST *> a);
  ~InnerExprAST();

protected:
  vector<ExprAST *> _nodes;

private:
  InnerExprAST(const InnerExprAST &i);
  InnerExprAST &operator=(const InnerExprAST &i);
};

class AddExprAST : public InnerExprAST {
public:
  AddExprAST(ExprAST *a, ExprAST *b) : InnerExprAST(a, b) {}
  Value *codegen() const;
};

class SubExprAST : public InnerExprAST {
public:
  SubExprAST(ExprAST *a, ExprAST *b) : InnerExprAST(a, b) {}
  Value *codegen() const;
};

class MulExprAST : public InnerExprAST {
public:
  MulExprAST(ExprAST *a, ExprAST *b) : InnerExprAST(a, b) {}
  Value *codegen() const;
};

class DivExprAST : public InnerExprAST {
public:
  DivExprAST(ExprAST *a, ExprAST *b) : InnerExprAST(a, b) {}
  Value *codegen() const;
};

class LTExprAST : public InnerExprAST {
public:
  LTExprAST(ExprAST *a, ExprAST *b) : InnerExprAST(a, b) {}
  Value *codegen() const;
};

class SeqExprAST : public InnerExprAST {
public:
  SeqExprAST(ExprAST *a, ExprAST *b) : InnerExprAST(a, b) {}
  Value *codegen() const;
};

class AssignExprAST : public InnerExprAST {
public:
  AssignExprAST(string s, ExprAST *a) : InnerExprAST(a), Name(s) {}
  Value *codegen() const;

private:
  string Name;
};

class GTExprAST : public InnerExprAST {
public:
  GTExprAST(ExprAST *a, ExprAST *b) : InnerExprAST(a, b) {}
  Value *codegen() const;
};

class CallExprAST : public InnerExprAST {
public:
  CallExprAST(string name, vector<ExprAST *> s)
      : InnerExprAST(s), Callee(name) {}
  Value *codegen() const;

private:
  string Callee;
};

class IfExprAST : public InnerExprAST {
public:
  IfExprAST(ExprAST *a, ExprAST *b, ExprAST *c) : InnerExprAST(a, b, c) {}
  Value *codegen() const;
};

class ForExprAST : public InnerExprAST {
public:
  ForExprAST(string s, ExprAST *a, ExprAST *b, ExprAST *c, ExprAST *d)
      : InnerExprAST(a, b, c, d), VarName(s) {}
  Value *codegen() const;

private:
  string VarName;
};

class VarExprAST : public InnerExprAST {
public:
  VarExprAST(vector<pair<string, ExprAST *>> v, ExprAST *a)
      : InnerExprAST(a), V(v) {}
  Value *codegen() const;
  ~VarExprAST();

private:
  VarExprAST &operator=(const VarExprAST &);
  VarExprAST(const VarExprAST &);
  vector<pair<string, ExprAST *>> V;
};

class PrintAST : public InnerExprAST {
public:
  PrintAST(ExprAST *e) : InnerExprAST(e) {}
  Value *codegen() const;

private:
  PrintAST(const PrintAST &);
  PrintAST &operator=(const PrintAST &);
};

class BlockAST : public InnerExprAST {
public:
  BlockAST(vector<ExprAST *> e) : InnerExprAST(e) {}
  Value *codegen() const;

private:
  BlockAST(const BlockAST &);
  BlockAST &operator=(const BlockAST &);
};

class WhileAST : public InnerExprAST {
public:
  WhileAST(ExprAST *a, ExprAST *b) : InnerExprAST(a, b) {}
  Value *codegen() const;

private:
  WhileAST(const WhileAST &);
  WhileAST &operator=(const WhileAST &);
};

class TypeAST {
public:
  TypeAST(Type *t, string v) : tip(t), str(v) {}
  ~TypeAST();

  Type *tip;
  string str;
};

class PrototypeAST {
public:
  PrototypeAST(Type *t, string n, vector<TypeAST *> a)
      : tip(t), Name(n), Args(a) {}
  Function *codegen() const;
  string getName() const { return Name; }

private:
  Type *tip;
  string Name;
  vector<TypeAST *> Args;
};

class FunctionAST {
public:
  FunctionAST(PrototypeAST p, ExprAST *b) : Proto(p), Body(b) {}
  ~FunctionAST();
  Function *codegen() const;

private:
  FunctionAST(const FunctionAST &f);
  FunctionAST &operator=(const FunctionAST &f);
  PrototypeAST Proto;
  ExprAST *Body;
};

class Declaration : public ExprAST {
public:
  Declaration(Type *t, vector<string> v) : tip(t), Vektor(v) {}

  Value *codegen() const;

private:
  Type *tip;
  vector<string> Vektor;
};

void InitializeModuleAndPassManager(void);
AllocaInst *CreateEntryBlockAlloca(Type *t, Function *TheFunction,
                                   const string &VarName);

#endif
