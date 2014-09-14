#include "Nil.h"

namespace Lispino {

Object* Nil::eval(Environment*) {
  return this;
}

int Nil::compare(const Object* obj) const {
  return obj->compareNil(this);
}

int Nil::compareNil(const Nil*) const {
  return 0;
}

int Nil::compareList(const List*) const {
  return -1;
}

int Nil::compareInt(const IntNumber*) const {
  return -1;
}

int Nil::compareFloat(const FloatNumber*) const {
  return -1;
}

int Nil::compareSymbol(const Symbol*) const {
  return -1;
}

int Nil::compareString(const String*) const {
  return -1;
}

int Nil::compareBoolean(const Boolean*) const {
  return -1;
}

int Nil::compareSequence(const Sequence*) const {
  return -1;
}

bool Nil::isNil() const {
  return true;
}

std::string Nil::toString() const {
  return "NIL";
}

}
