#include "Nil.h"

namespace lispino {

int Nil::compare(const Object* obj) const throw(errors::RuntimeError) {
  return obj->compareNil(this);
}

int Nil::compareNil(const Nil*) const throw(errors::RuntimeError) {
  return 0;
}

int Nil::compareList(const List*) const throw(errors::RuntimeError) {
  return -1;
}

int Nil::compareInt(const IntNumber*) const throw(errors::RuntimeError) {
  return -1;
}

int Nil::compareFloat(const FloatNumber*) const throw(errors::RuntimeError) {
  return -1;
}

int Nil::compareSymbol(const Symbol*) const throw(errors::RuntimeError) {
  return -1;
}

int Nil::compareString(const String*) const throw(errors::RuntimeError) {
  return -1;
}

int Nil::compareBoolean(const Boolean*) const throw(errors::RuntimeError) {
  return -1;
}

std::string Nil::toString() const {
  return "nil";
}
}
