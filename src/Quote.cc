#include "Quote.h"

namespace Lispino {

Quote::Quote() : value(nullptr) {
  /* DO NOTHING */
}

Quote::Quote(Object* value) : value(value) {
  /* DO NOTHING */
}

void Quote::setValue(Object* value) {
  this->value = value;
}

Object* Quote::getValue() {
  return value;
}

Object* Quote::eval(Environment&) {
  return value;
}

void Quote::mark() {
  Object::mark();
  value->mark();
}

bool Quote::isQuote() const {
  return true;
}

std::string Quote::toString() const {
  return "'" + value->toString();
}

}
