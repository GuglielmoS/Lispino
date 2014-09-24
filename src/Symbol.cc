#include "Symbol.h"

#include <sstream>

#include "Environment.h"

namespace Lispino {

Symbol::Symbol() : Object(ObjectType::SYMBOL), value("") {
  /* DO NOTHING */
}

Symbol::Symbol(std::string value) : Object(ObjectType::SYMBOL), value(value) {
  /* DO NOTHING */
}

void Symbol::setValue(std::string value) {
  this->value = value;
}

std::string Symbol::getValue() const {
  return value;
}

int Symbol::compare(const Object* obj) const throw (Errors::RuntimeError) {
  if (obj == this)
    return 0;
  else 
    return obj->compareSymbol(this);
}

int Symbol::compareSymbol(const Symbol* obj) const throw (Errors::RuntimeError) {
  return obj->getValue().compare(value);
}

std::string Symbol::toString() const {
  return value;
}

}
