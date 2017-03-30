#ifndef __NAREDBA_HPP__
#define __NAREDBA_HPP__ 1
#include <string>
#include "izraz.hpp"

#include <vector>

using namespace std;

class Naredba {
public:
  virtual void izvrsi() const = 0;
  virtual ~Naredba()
  { }
  virtual void ispis(int d = 0) const = 0;
};

class IspisIzraza : public Naredba {
public:
  IspisIzraza(Izraz *i)
    : _i(i->klon())
  {}
  void izvrsi() const;
  ~IspisIzraza();
  IspisIzraza(const IspisIzraza &n);
  IspisIzraza& operator=(const IspisIzraza &n);
  void ispis(int d = 0) const;
private:
  Izraz* _i;
};

class IspisStringa : public Naredba {
public:
  IspisStringa(string s)
    :_s(s)
  {}
  void izvrsi() const;
  void ispis(int d = 0) const;
private:
  string _s;
};

class Dodela : public Naredba {
public:
  Dodela(string l, Izraz* i)
    : _l(l), _i(i->klon())
  {}
  void izvrsi() const;
  ~Dodela();
  Dodela(const Dodela& n);
  Dodela& operator=(const Dodela& n);
  void ispis(int d = 0) const;
private:
  string _l;
  Izraz* _i;
};

class Blok : public Naredba {
public:
  Blok(vector<Naredba *> v)
    : _v(v)
  {}
  void izvrsi() const;
  ~Blok();
  void ispis(int d = 0) const;
private:
  Blok(const Blok &n);
  Blok& operator=(const Blok &n);
  vector<Naredba *> _v;
};

class AkoJeOnda : public Naredba {
public:
  AkoJeOnda(Izraz* i, Naredba* n1)
    : _i(i->klon()), _n1(n1)
  {}
  void izvrsi() const;
  ~AkoJeOnda();
  void ispis(int d = 0) const;
private:
  AkoJeOnda(const AkoJeOnda &n);
  AkoJeOnda& operator=(const AkoJeOnda &n);
  Izraz* _i;
  Naredba* _n1;
};

class AkoJeOndaInace : public Naredba {
public:
  AkoJeOndaInace(Izraz* i, Naredba* n1, Naredba* n2)
    : _i(i->klon()), _n1(n1), _n2(n2)
  {}
  void izvrsi() const;
  ~AkoJeOndaInace();
  void ispis(int d = 0) const;
private:
  AkoJeOndaInace(const AkoJeOndaInace &n);
  AkoJeOndaInace& operator=(const AkoJeOndaInace &n);
  Izraz* _i;
  Naredba* _n1;
  Naredba* _n2;
};

class Unesi : public Naredba {
public:
  Unesi(string s)
    :_s(s)
  {}
  void izvrsi() const;
  void ispis(int d = 0) const;
private:
  string _s;
};

class DokJe : public Naredba {
public:
  DokJe(Izraz* i, Naredba* n1)
    : _i(i->klon()), _n1(n1)
  {}
  void izvrsi() const;
  ~DokJe();
  void ispis(int d = 0) const;
private:
  DokJe(const DokJe &n);
  DokJe& operator=(const DokJe &n);
  Izraz* _i;
  Naredba* _n1;
};

#endif
