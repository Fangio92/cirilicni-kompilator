#include "izraz.hpp"

#include <map>
using namespace std;

extern map<string, int> tablica;

int Konstanta::vrednost() const {
  return _c;
}

Izraz* Konstanta::klon() const {
  return new Konstanta(*this);
}

void Konstanta::ispis() const {
  cout << _c;
}

int Promenljiva::vrednost() const {
  if (tablica.count(_ime))
    return tablica[_ime];
  else {
    cerr << "Nedefinisana promenljiva " << _ime << endl;
    exit(EXIT_FAILURE);
  }
}
Izraz* Promenljiva::klon() const {
  return new Promenljiva(*this);
}

void Promenljiva::ispis() const {
  cout << _ime;
}

BinOperator::~BinOperator () {
  delete _levi;
  delete _desni;
}

BinOperator::BinOperator(const BinOperator& z) {
  _levi = z._levi->klon();
  _desni = z._desni->klon();
}

BinOperator& BinOperator::operator=(const BinOperator& z) {
  if (this != &z) {
    delete _levi;
    delete _desni;
    _levi = z._levi->klon();
    _desni = z._desni->klon();
  }
  return *this;
}

int Zbir::vrednost() const {
  return _levi->vrednost() + _desni->vrednost();
}

Izraz* Zbir::klon() const {
  return new Zbir(*this);
}

void Zbir::ispis() const {
  _levi->ispis();
  cout << " + ";
  _desni->ispis();
}

int Razlika::vrednost() const {
  return _levi->vrednost() - _desni->vrednost();
}

Izraz* Razlika::klon() const {
  return new Razlika(*this);
}

void Razlika::ispis() const {
  _levi->ispis();
  cout << " - ";
  _desni->ispis();
}

int Proizvod::vrednost() const {
  return _levi->vrednost() * _desni->vrednost();
}

Izraz* Proizvod::klon() const {
  return new Proizvod(*this);
}

void Proizvod::ispis() const {
  _levi->ispis();
  cout << " * ";
  _desni->ispis();
}

int Kolicnik::vrednost() const {
  return _levi->vrednost() / _desni->vrednost();
}

Izraz* Kolicnik::klon() const {
  return new Kolicnik(*this);
}

void Kolicnik::ispis() const {
  _levi->ispis();
  cout << " / ";
  _desni->ispis();
}

int Mod::vrednost() const {
  return _levi->vrednost() % _desni->vrednost();
}

Izraz* Mod::klon() const {
  return new Mod(*this);
}

void Mod::ispis() const {
  _levi->ispis();
  cout << " mod ";
  _desni->ispis();
}

int Vece::vrednost() const {
  return _levi->vrednost() > _desni->vrednost();
}

Izraz* Vece::klon() const {
  return new Vece(*this);
}

void Vece::ispis() const {
  _levi->ispis();
  cout << " > ";
  _desni->ispis();
}

int Manje::vrednost() const {
  return _levi->vrednost() < _desni->vrednost();
}

Izraz* Manje::klon() const {
  return new Manje(*this);
}

void Manje::ispis() const {
  _levi->ispis();
  cout << " < ";
  _desni->ispis();
}
