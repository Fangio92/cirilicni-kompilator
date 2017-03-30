#include "naredba.hpp"

#include <map>
#include <iostream>

using namespace std;

void IspisIzraza::izvrsi() const {
  cout << _i->vrednost() << endl;
}

IspisIzraza::~IspisIzraza() {
  delete _i;
}

IspisIzraza::IspisIzraza(const IspisIzraza &n) {
  _i = n._i->klon();
}

IspisIzraza& IspisIzraza::operator=(const IspisIzraza &n) {
  if (this != &n) {
    delete _i;
    _i = n._i->klon();
  }
  return *this;
}

void IspisIzraza::ispis(int d) const {
  for (int j = 0; j < d; j++)
    cout << "\t";
  cout << "ispisi(";
  _i->ispis();
  cout << ")";
}

void IspisStringa::izvrsi() const {
  cout << _s << endl;
}

void IspisStringa::ispis(int d) const {
  for (int j = 0; j < d; j++)
    cout << "\t";
  cout << "ispisi(\"" << _s << "\")";
}

extern map<string, int> tablica;

void Dodela::izvrsi() const {
  tablica[_l] = _i->vrednost();
}

Dodela::~Dodela() {
  delete _i;
}

Dodela::Dodela(const Dodela& n) {
  _i = n._i->klon();
  _l = n._l;
}

Dodela& Dodela::operator=(const Dodela& n) {
  if (this != &n) {
    delete _i;
    _i = n._i->klon();
    _l = n._l;
  }
  return *this;
}

void Dodela::ispis(int d) const {
  for (int j = 0; j < d; j++)
    cout << "\t";
  cout << _l << " := ";
  _i->ispis();
}

void Blok::izvrsi() const {
  for (auto n : _v)
    n->izvrsi();
}

Blok::~Blok() {
  for (auto n : _v)
    delete n;
}

void Blok::ispis(int d) const {
  for (int j = 0; j < d; j++)
    cout << "\t";
  cout << "pocetak" << endl;
  for (unsigned i = 0; i < _v.size(); i++) {
    _v[i]->ispis(d+1);
    if (i < _v.size() - 1)
      cout << ";";
    cout << endl;
  }
  for (int j = 0; j < d; j++)
    cout << "\t";
  cout << "kraj";
}

void AkoJeOnda::izvrsi() const {
  if (_i->vrednost())
    _n1->izvrsi();
}

AkoJeOnda::~AkoJeOnda() {
  delete _i;
  delete _n1;
}

void AkoJeOnda::ispis(int d) const {
  for (int j = 0; j < d; j++)
    cout << "\t";
  cout << "ako_je ";
  _i->ispis();
  cout << " onda:" << endl;
  _n1->ispis(d+1);
}

void AkoJeOndaInace::izvrsi() const {
  if (_i->vrednost())
    _n1->izvrsi();
  else
    _n2->izvrsi();
}

AkoJeOndaInace::~AkoJeOndaInace() {
  delete _i;
  delete _n1;
  delete _n2;
}

void AkoJeOndaInace::ispis(int d) const {
  for (int j = 0; j < d; j++)
    cout << "\t";
  cout << "ako_je ";
  _i->ispis();
  cout << " onda:" << endl;
  _n1->ispis(d+1);
  cout << endl;
  for (int j = 0; j < d; j++)
    cout << "\t";
  cout << "inace: " << endl;
  _n2->ispis(d+1);
}

void Unesi::izvrsi() const {
  int tmp;
  cin >> tmp;
  tablica[_s] = tmp;
}

void Unesi::ispis(int d) const {
  for (int j = 0; j < d; j++)
    cout << "\t";
  cout << "unesi(" << _s << ")";
}

void DokJe::izvrsi() const {
  while (_i->vrednost())
    _n1->izvrsi();
}

DokJe::~DokJe() {
  delete _i;
  delete _n1;
}

void DokJe::ispis(int d) const {
  for (int j = 0; j < d; j++)
    cout << "\t";
  cout << "dok_je ";
  _i->ispis();
  cout << " radi_sledece:" << endl;
  _n1->ispis(d+1);
}
