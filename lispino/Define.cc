#include "Define.h"

#include "Environment.h"

namespace lispino {

Define::Define() : Object(ObjectType::DEFINE), name(nullptr), value(nullptr) {
  /* DO NOTHING */
}

Define::Define(Symbol* name, Object* value) : Object(ObjectType::DEFINE), name(name), value(value) {
  /* DO NOTHING */
}

void Define::setName(Symbol* name) {
  this->name = name;
}

void Define::setValue(Object* value) {
  this->value = value;
}

std::string Define::getName() const {
  return name->getValue();
}

Symbol* Define::getSymbol() {
  return name;
}

Object* Define::getValue() {
  return value;
}

std::string Define::toString() const {
  return "DEFINE";
}
}
