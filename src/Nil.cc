#include "Nil.h"

namespace Lispino {

int Nil::compare(const Object* obj) const throw (Errors::RuntimeError) {
  return obj->compareNil(this);
}

int Nil::compareNil(const Nil*) const throw (Errors::RuntimeError) {
  return 0;
}

int Nil::compareList(const List*) const throw (Errors::RuntimeError) {
  return -1;
}

int Nil::compareInt(const IntNumber*) const throw (Errors::RuntimeError) {
  return -1;
}

int Nil::compareFloat(const FloatNumber*) const throw (Errors::RuntimeError) {
  return -1;
}

int Nil::compareSymbol(const Symbol*) const throw (Errors::RuntimeError) {
  return -1;
}

int Nil::compareString(const String*) const throw (Errors::RuntimeError) {
  return -1;
}

int Nil::compareBoolean(const Boolean*) const throw (Errors::RuntimeError) {
  return -1;
}

int Nil::compareSequence(const Sequence*) const throw (Errors::RuntimeError) {
  return -1;
}

std::string Nil::toString() const {
  return "NIL";
}

}
