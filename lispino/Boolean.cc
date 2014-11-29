#include "Boolean.h"

namespace lispino {

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

int Boolean::compare(const Object* obj) const throw(errors::RuntimeError) {
  return obj->compareBoolean(this);
}

int Boolean::compareBoolean(const Boolean* obj) const throw(errors::RuntimeError) {
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

std::string Boolean::toString() const {
  return value ? "#t" : "#f";
}
}
