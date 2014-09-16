#include "Define.h"

#include "Environment.h"

namespace Lispino {

Define::Define() : name(nullptr), value(nullptr) {
  /* DO NOTHING */
}

Define::Define(Symbol* name, Object* value) : name(name), value(value) {
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

Object* Define::getValue() {
  return value;
}

Object* Define::eval(Environment* env) throw (Errors::RuntimeError) {
  if (value->isLambda())
    return env->put(name, value);
  else
    return env->put(name, value->eval(env));
}

void Define::mark() {
  Object::mark();
  name->mark();
  value->mark();
}

bool Define::isDefine() const {
  return true;
}

std::string Define::toString() const {
  return "DEFINE";
}

}
