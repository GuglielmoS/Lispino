#include "Quote.h"

namespace Lispino {

Quote::Quote() : Object(ObjectType::QUOTE), value(nullptr) {
  /* DO NOTHING */
}

Quote::Quote(Object* value) : Object(ObjectType::QUOTE), value(value) {
  /* DO NOTHING */
}

void Quote::setValue(Object* value) {
  this->value = value;
}

Object* Quote::getValue() {
  return value;
}

void Quote::mark() {
  Object::mark();
  value->mark();
}

std::string Quote::toString() const {
  return "'" + value->toString();
}

}
