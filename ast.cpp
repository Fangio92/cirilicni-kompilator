#include "ast.hpp"

#include "llvm/IR/Type.h"
#include <algorithm>
#include <iostream>

LLVMContext TheContext;
map<string, AllocaInst *> NamedValues;
IRBuilder<> Builder(TheContext);
Module *TheModule;
FunctionPassManager *TheFPM;

ExprAST::~ExprAST() {}

TypeAST::~TypeAST() {}

InnerExprAST::InnerExprAST(ExprAST *a) {
  _nodes.resize(0);
  _nodes.push_back(a);
}

InnerExprAST::InnerExprAST(ExprAST *a, ExprAST *b) {
  _nodes.resize(0);
  _nodes.push_back(a);
  _nodes.push_back(b);
}

InnerExprAST::InnerExprAST(ExprAST *a, ExprAST *b, ExprAST *c) {
  _nodes.resize(0);
  _nodes.push_back(a);
  _nodes.push_back(b);
  _nodes.push_back(c);
}

InnerExprAST::InnerExprAST(ExprAST *a, ExprAST *b, ExprAST *c, ExprAST *d) {
  _nodes.resize(0);
  _nodes.push_back(a);
  _nodes.push_back(b);
  _nodes.push_back(c);
  _nodes.push_back(d);
}

InnerExprAST::InnerExprAST(vector<ExprAST *> a) { _nodes = a; }

InnerExprAST::~InnerExprAST() {
  for (unsigned i = 0; i < _nodes.size(); i++)
    delete _nodes[i];
}

FunctionAST::~FunctionAST() { delete Body; }

Value *NumberDExprAST::codegen() const {
  return ConstantFP::get(TheContext, APFloat(Val));
}

Value *NumberIExprAST::codegen() const {
  return ConstantInt::get(TheContext, APInt(32, Val));
}

Value *VariableExprAST::codegen() const {
  AllocaInst *tmp = NamedValues[Name];
  if (tmp == NULL) {
    cerr << "Promenljiva " + Name + " nije definisana!" << endl;
    return NULL;
  }

  if (tmp->getType()->getElementType()->isDoubleTy()) {
    return Builder.CreateLoad(Type::getDoubleTy(TheContext), tmp, Name.c_str());
  } else {
    return Builder.CreateLoad(Type::getInt32Ty(TheContext), tmp, Name.c_str());
  }
}

Value *AddExprAST::codegen() const {
  Value *l = _nodes[0]->codegen();
  Value *d = _nodes[1]->codegen();

  if (l == NULL || d == NULL)
    return NULL;

  bool bl = l->getType()->isDoubleTy();
  bool bd = d->getType()->isDoubleTy();

  // oba int
  if (!bl && !bd)
    return Builder.CreateAdd(l, d, "addtmp");

  // oba double
  if (bl && bd)
    return Builder.CreateFAdd(l, d, "addtmp");

  // znaci jedan je int, konvertuj ga
  if (!bl) {
    l = Builder.CreateSIToFP(l, Type::getDoubleTy(TheContext), "conv");
  } else {
    d = Builder.CreateSIToFP(d, Type::getDoubleTy(TheContext), "conv");
  }

  return Builder.CreateFAdd(l, d, "addtmp");
}

Value *SubExprAST::codegen() const {
  Value *l = _nodes[0]->codegen();
  Value *d = _nodes[1]->codegen();

  bool bl = l->getType()->isDoubleTy();
  bool bd = d->getType()->isDoubleTy();

  // oba int
  if (!bl && !bd)
    return Builder.CreateSub(l, d, "subtmp");

  // oba double
  if (bl && bd)
    return Builder.CreateFSub(l, d, "subtmp");

  // znaci jedan je int, konvertuj ga
  if (!bl) {
    l = Builder.CreateSIToFP(l, Type::getDoubleTy(TheContext), "conv");
  } else {
    d = Builder.CreateSIToFP(d, Type::getDoubleTy(TheContext), "conv");
  }

  return Builder.CreateFSub(l, d, "subtmp");
}

Value *MulExprAST::codegen() const {
  Value *l = _nodes[0]->codegen();
  Value *d = _nodes[1]->codegen();
  if (l == NULL || d == NULL)
    return NULL;

  bool bl = l->getType()->isDoubleTy();
  bool bd = d->getType()->isDoubleTy();

  // oba int
  if (!bl && !bd)
    return Builder.CreateMul(l, d, "multmp");

  // oba double
  if (bl && bd)
    return Builder.CreateFMul(l, d, "multmp");

  // znaci jedan je int, konvertuj ga
  if (!bl) {
    l = Builder.CreateSIToFP(l, Type::getDoubleTy(TheContext), "conv");
  } else {
    d = Builder.CreateSIToFP(d, Type::getDoubleTy(TheContext), "conv");
  }

  return Builder.CreateFMul(l, d, "multmp");
}

Value *DivExprAST::codegen() const {
  Value *l = _nodes[0]->codegen();
  Value *d = _nodes[1]->codegen();
  if (l == NULL || d == NULL)
    return NULL;

  bool bl = l->getType()->isDoubleTy();
  bool bd = d->getType()->isDoubleTy();

  if (!bl) {
    l = Builder.CreateSIToFP(l, Type::getDoubleTy(TheContext), "conv");
  }
  if (!bd) {
    d = Builder.CreateSIToFP(d, Type::getDoubleTy(TheContext), "conv");
  }

  return Builder.CreateFDiv(l, d, "divtmp");
}

Value *LTExprAST::codegen() const {
  Value *l = _nodes[0]->codegen();
  Value *d = _nodes[1]->codegen();

  if (l == NULL || d == NULL)
    return NULL;

  bool bl = l->getType()->isDoubleTy();
  bool bd = d->getType()->isDoubleTy();
  
  if (!bl) {
    l = Builder.CreateSIToFP(l, Type::getDoubleTy(TheContext), "conv");
  }
  if (!bd) {
    d = Builder.CreateSIToFP(d, Type::getDoubleTy(TheContext), "conv");
  }

  l = Builder.CreateFCmpULT(l, d, "lttmp");
  return Builder.CreateUIToFP(l, Type::getDoubleTy(TheContext), "booltmp");
}

Value *GTExprAST::codegen() const {
  Value *l = _nodes[0]->codegen();
  Value *d = _nodes[1]->codegen();
  if (l == NULL || d == NULL)
    return NULL;

  bool bl = l->getType()->isDoubleTy();
  bool bd = d->getType()->isDoubleTy();
  

  if (!bl) {
    l = Builder.CreateSIToFP(l, Type::getDoubleTy(TheContext), "conv");
  }
  if (!bd) {
    d = Builder.CreateSIToFP(d, Type::getDoubleTy(TheContext), "conv");
  }

  l = Builder.CreateFCmpUGT(l, d, "gttmp");
  return Builder.CreateUIToFP(l, Type::getDoubleTy(TheContext), "booltmp");
}

Value *SeqExprAST::codegen() const {
  Value *l = _nodes[0]->codegen();
  Value *d = _nodes[1]->codegen();
  if (l == NULL || d == NULL)
    return NULL;
  return d;
}

Value *AssignExprAST::codegen() const {
  Value *tmp = _nodes[0]->codegen();
  if (tmp == NULL)
    return NULL;

  AllocaInst *Alloca = NamedValues[Name];

  if (Alloca == NULL) {
    cerr << "Promenljiva " + Name + " nije definisana!" << endl;
    return NULL;
  }

  bool bl = tmp->getType()->isDoubleTy();
  bool bd = Alloca->getType()->getElementType()->isDoubleTy();

  if (bl != bd) {
    cerr << "Promenljiva " + Name +
                " se ne poklapa sa tipom koji joj je dodeljen!"
         << endl;
    return NULL;
  }

  Builder.CreateStore(tmp, Alloca);
  return tmp;
}

Value *CallExprAST::codegen() const {
  Function *CalleeF = TheModule->getFunction(Callee);
  if (!CalleeF) {
    cerr << "Funkcija " << Callee << " nije definisana!" << endl;
    return NULL;
  }

  if (CalleeF->arg_size() != _nodes.size()) {
    cout << "Funkcija " << Callee << " prima " << CalleeF->arg_size()
         << " argumenata!" << endl;
    return NULL;
  }

  vector<Value *> ArgsV;
  for (unsigned i = 0, e = _nodes.size(); i != e; ++i) {
    ArgsV.push_back(_nodes[i]->codegen());
    if (!ArgsV.back())
      return NULL;
  }

  return Builder.CreateCall(CalleeF, ArgsV, "calltmp");
}

Value *IfExprAST::codegen() const {
  Value *CondV = _nodes[0]->codegen();
  if (CondV == NULL)
    return NULL;

  CondV = Builder.CreateFCmpONE(
      CondV, ConstantFP::get(TheContext, APFloat(0.0)), "ifcond");
  Function *TheFunction = Builder.GetInsertBlock()->getParent();

  BasicBlock *ThenBB = BasicBlock::Create(TheContext, "then", TheFunction);
  BasicBlock *ElseBB = BasicBlock::Create(TheContext, "else");
  BasicBlock *MergeBB = BasicBlock::Create(TheContext, "ifcont");

  Builder.CreateCondBr(CondV, ThenBB, ElseBB);

  Builder.SetInsertPoint(ThenBB);
  Value *ThenV = _nodes[1]->codegen();
  if (ThenV == NULL)
    return NULL;
  Builder.CreateBr(MergeBB);
  ThenBB = Builder.GetInsertBlock();

  TheFunction->getBasicBlockList().push_back(ElseBB);
  Builder.SetInsertPoint(ElseBB);
  Value *ElseV = _nodes[2]->codegen();
  if (ElseV == NULL)
    return NULL;
  Builder.CreateBr(MergeBB);
  ElseBB = Builder.GetInsertBlock();

  TheFunction->getBasicBlockList().push_back(MergeBB);
  Builder.SetInsertPoint(MergeBB);

  PHINode *PN;

  bool bl = ThenV->getType()->isDoubleTy();
  bool bd = ElseV->getType()->isDoubleTy();

  // oba int
  if (!bl && !bd) {
    PN = Builder.CreatePHI(Type::getInt32Ty(TheContext), 2, "iftmp");
    PN->addIncoming(ThenV, ThenBB);
    PN->addIncoming(ElseV, ElseBB);
    return PN;
  }

  // oba double
  if (bl && bd) {
    PN = Builder.CreatePHI(Type::getDoubleTy(TheContext), 2, "iftmp");
    PN->addIncoming(ThenV, ThenBB);
    PN->addIncoming(ElseV, ElseBB);
    return PN;
  }

  // znaci jedan je int, konvertuj ga
  if (!bl) {
    ThenV = Builder.CreateSIToFP(ThenV, Type::getDoubleTy(TheContext), "conv");
  } else {
    ElseV = Builder.CreateSIToFP(ElseV, Type::getDoubleTy(TheContext), "conv");
  }

  PN = Builder.CreatePHI(Type::getDoubleTy(TheContext), 2, "iftmp");
  PN->addIncoming(ThenV, ThenBB);
  PN->addIncoming(ElseV, ElseBB);
  return PN;
}

Function *PrototypeAST::codegen() const {
  vector<Type *> tipovi;

  for (unsigned i = 0; i < Args.size(); ++i) {
    tipovi.push_back(Args[i]->tip);
  }
  vector<Type *> Doubles(Args.size(), Type::getDoubleTy(TheContext));

  FunctionType *FT = FunctionType::get(tip, tipovi, false);

  Function *F =
      Function::Create(FT, Function::ExternalLinkage, Name, TheModule);

  unsigned Idx = 0;
  for (auto &Arg : F->args())
    Arg.setName(Args[Idx++]->str);

  return F;
}

Function *FunctionAST::codegen() const {
  Function *TheFunction;

  TheFunction = TheModule->getFunction(Proto.getName());

  if (!TheFunction)
    TheFunction = Proto.codegen();

  if (!TheFunction)
    return NULL;

  if (!TheFunction->empty()) {
    cerr << "Nije dozvoljeno predefinisanje funkcije " << Proto.getName() << endl;
    return NULL;
  }

  BasicBlock *BB = BasicBlock::Create(TheContext, "entry", TheFunction);
  Builder.SetInsertPoint(BB);

  NamedValues.clear();
  for (auto &Arg : TheFunction->args()) {
    AllocaInst *Alloca =
        CreateEntryBlockAlloca(Arg.getType(), TheFunction, Arg.getName());
    NamedValues[Arg.getName()] = Alloca;
    Builder.CreateStore(&Arg, Alloca);
  }

  if (Value *RetVal = Body->codegen()) {
    Builder.CreateRet(RetVal);
    verifyFunction(*TheFunction);
    TheFPM->run(*TheFunction);
    return TheFunction;
  }
  TheFunction->eraseFromParent();

  return NULL;
}

extern Function *PrintfFja;

Value *PrintAST::codegen() const {
  Value *r = _nodes[0]->codegen();
  if (r == NULL)
    return NULL;

  Value *Str = NULL;

  if (r->getType()->isDoubleTy())
    Str = Builder.CreateGlobalStringPtr("[ %g ]\n");
  else
    Str = Builder.CreateGlobalStringPtr("[ %d ]\n");

  vector<Value *> ArgsV1;
  ArgsV1.push_back(Str);
  ArgsV1.push_back(r);

  return Builder.CreateCall(PrintfFja, ArgsV1, "printfCall");
}

Value *BlockAST::codegen() const {
  unsigned size = _nodes.size() - 1;

  for (unsigned i = 0; i < size; i++)
    _nodes[i]->codegen();

  return _nodes[size]->codegen();
}

Value *Declaration::codegen() const {
  Function *TheFunction = Builder.GetInsertBlock()->getParent();

  for (unsigned i = 0; i < Vektor.size(); i++) {
    AllocaInst *Alloca = CreateEntryBlockAlloca(tip, TheFunction, Vektor[i]);

    Value *tmp = NULL;
    if (tip == Type::getDoubleTy(TheContext))
      tmp = ConstantFP::get(TheContext, APFloat(0.0));
    if (tip == Type::getInt32Ty(TheContext))
      tmp = ConstantInt::get(TheContext, APInt(32, 0));

    if (tmp == NULL)
      return NULL;

    NamedValues[Vektor[i]] = Alloca;
    Builder.CreateStore(tmp, Alloca);
  }

  return NULL;
}

Value *WhileAST::codegen() const {
  Function *TheFunction = Builder.GetInsertBlock()->getParent();
  
  BasicBlock *LoopBB = BasicBlock::Create(TheContext, "whileloop", TheFunction);
  BasicBlock *AfterLoopBB =
      BasicBlock::Create(TheContext, "afterloop", TheFunction);

  Value *CondV = _nodes[0]->codegen();
  if (CondV == NULL)
    return NULL;
  CondV = Builder.CreateFCmpONE(
      CondV, ConstantFP::get(TheContext, APFloat(0.0)), "loopcond");

  Builder.CreateCondBr(CondV, LoopBB, AfterLoopBB);

  Builder.SetInsertPoint(LoopBB);

  Value *BodyV = _nodes[1]->codegen();
  if (BodyV == NULL)
    return NULL;

  CondV = _nodes[0]->codegen();
  if (CondV == NULL)
    return NULL;

  CondV = Builder.CreateFCmpONE(
      CondV, ConstantFP::get(TheContext, APFloat(0.0)), "loopcond");

  Builder.CreateCondBr(CondV, LoopBB, AfterLoopBB);

  Builder.SetInsertPoint(AfterLoopBB);
  
  return BodyV;
}

void InitializeModuleAndPassManager(void) {
  TheModule = new Module("my_module", TheContext);

  TheFPM = new FunctionPassManager(TheModule);

  if (OPTIMIZE) {
    TheFPM->add(createInstructionCombiningPass());
    TheFPM->add(createReassociatePass());
    TheFPM->add(createGVNPass());
    TheFPM->add(createCFGSimplificationPass());
    TheFPM->add(createPromoteMemoryToRegisterPass());
  }
  TheFPM->doInitialization();
}

AllocaInst *CreateEntryBlockAlloca(Type *tip, Function *TheFunction,
                                   const string &VarName) {
  IRBuilder<> TmpB(&TheFunction->getEntryBlock(),
                   TheFunction->getEntryBlock().begin());

  return TmpB.CreateAlloca(tip, 0, VarName.c_str());
}
