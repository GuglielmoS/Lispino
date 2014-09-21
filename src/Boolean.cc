#include "Boolean.h"

namespace Lispino {

Boolean::Boolean() : Object(ObjectType::BOOLEAN), value(false) {
  /* DO NOTHING */
}

Boolean::Boolean(bool value) : Object(ObjectType::BOOLEAN), value(value) {
  /* DO NOTHING */
}

void Boolean::setValue(bool value) {
  this->value = value;
}

bool Boolean::getValue() const {
  return value;
}

Object* Boolean::eval(Environment*) throw (Errors::RuntimeError) {
  return this;
}

int Boolean::compare(const Object* obj) const throw (Errors::RuntimeError) {
  return obj->compareBoolean(this);
}

int Boolean::compareBoolean(const Boolean* obj) const throw (Errors::RuntimeError) {
  if (value == obj->value)
    return 0;
  else if (value == false)
    return 1;
  else
    return -1;
}

bool Boolean::isTrue() const {
  return value;
}

bool Boolean::isFalse() const {
  return !value;
}

bool Boolean::isBoolean() const {
  return true;
}

std::string Boolean::toString() const {
  return value ? "TRUE" : "FALSE";
}

}
