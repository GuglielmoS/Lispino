#include "Nil.h"

namespace Lispino {
Object* Nil::eval(Environment&) {
  return this;
}

int Nil::compare(Object* obj) {
  return obj->compareNil(this);
}

int Nil::compareNil(Nil*) {
  return 0;
}

int Nil::compareList(List*) {
  return -1;
}

int Nil::compareInt(IntNumber*) {
  return -1;
}

int Nil::compareFloat(FloatNumber*) {
  return -1;
}

int Nil::compareSymbol(Symbol*) {
  return -1;
}

int Nil::compareString(String*) {
  return -1;
}

int Nil::compareBoolean(Boolean*) {
  return -1;
}

int Nil::compareSequence(Sequence*) {
  return -1;
}

bool Nil::isNil() const {
  return true;
}

std::string Nil::toString() const {
  return "NIL";
}

}
