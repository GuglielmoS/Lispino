#include "Quote.h"

namespace lispino {

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

std::string Quote::toString() const {
  return "'" + value->toString();
}
}
