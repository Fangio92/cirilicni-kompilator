#ifndef __IZRAZ_HPP__ 
#define __IZRAZ_HPP__ 1

#include <iostream>
#include <string>
#include <map>
#include <cstdlib>

using namespace std;

class Izraz {
public:
  virtual int vrednost() const = 0;
  virtual Izraz* klon() const = 0;
  virtual ~Izraz() {

  }
  virtual void ispis() const = 0;
};

class Konstanta : public Izraz {
public:
  Konstanta(int c)
    :_c(c)
  {}
  int vrednost() const;
  Izraz* klon() const;
  void ispis() const;
private:
  int _c;
};

class Promenljiva : public Izraz {
public:
  Promenljiva(string ime)
    :_ime(ime)
  {}
  int vrednost() const;
  Izraz* klon() const;
  void ispis() const;
private:
  string _ime;
};

class BinOperator : public Izraz {
public:
  BinOperator(Izraz* levi, Izraz* desni)
    :_levi(levi->klon()), _desni(desni->klon())
  {}
  ~BinOperator ();
  BinOperator(const BinOperator& z);
  BinOperator& operator=(const BinOperator& z);
protected:  
  Izraz* _levi;
  Izraz* _desni;
};

class Zbir : public BinOperator {
public:
  Zbir(Izraz* i1, Izraz* i2)
    :BinOperator(i1, i2)
  {}
  int vrednost() const;
  Izraz* klon() const;
  void ispis() const;
};

class Razlika : public BinOperator {
public:
  Razlika(Izraz* i1, Izraz* i2)
    :BinOperator(i1, i2)
  {}
  int vrednost() const ;
  Izraz* klon() const ;
  void ispis() const;
};

class Proizvod : public BinOperator {
public:
  Proizvod(Izraz* i1, Izraz* i2)
    :BinOperator(i1, i2)
  {}
  int vrednost() const;
  Izraz* klon() const;
  void ispis() const;
};

class Kolicnik : public BinOperator {
public:
  Kolicnik(Izraz* i1, Izraz* i2)
    :BinOperator(i1, i2)
  {}
  int vrednost() const;
  Izraz* klon() const ;
  void ispis() const;
};

class Mod : public BinOperator {
public:
  Mod(Izraz* i1, Izraz* i2)
    :BinOperator(i1, i2)
  {}
  int vrednost() const;
  Izraz* klon() const ;
  void ispis() const;
};

class Vece : public BinOperator {
public:
  Vece(Izraz* i1, Izraz* i2)
    :BinOperator(i1, i2)
  {}
  int vrednost() const;
  Izraz* klon() const ;
  void ispis() const;
};

class Manje : public BinOperator {
public:
  Manje(Izraz* i1, Izraz* i2)
    :BinOperator(i1, i2)
  {}
  int vrednost() const;
  Izraz* klon() const ;
  void ispis() const;
};

#endif
