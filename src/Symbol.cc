#include "Symbol.h"

#include "Environment.h"

namespace Lispino {

Symbol::Symbol() : value("") {
  /* DO NOTHING */
}

Symbol::Symbol(std::string value) : value(value) {
  /* DO NOTHING */
}

void Symbol::setValue(std::string value) {
  this->value = value;
}

std::string Symbol::getValue() const {
  return value;
}

Object* Symbol::eval(Environment* env) throw (Errors::RuntimeError) {
  return env->get(this);
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

bool Symbol::isAtom() const {
  return true;
}

bool Symbol::isSymbol() const {
  return true;
}

std::string Symbol::toString() const {
  return value;
}

}
