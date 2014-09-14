#include "Closure.h"
#include "VM.h"

namespace Lispino {

Closure::Closure() : lambda(nullptr), env(nullptr) {
  /* DO NOTHING */
}

Closure::Closure(Lambda *lambda, Environment *env)
    : lambda(lambda), env(env) {
  /* DO NOTHING */    
}

void Closure::setLambda(Lambda *lambda) {
  this->lambda = lambda;
}

void Closure::setEnv(Environment *env) {
  this->env.reset(env);
}

Lambda* Closure::getLambda() {
  return lambda;
}

Environment* Closure::getEnv() {
  return env.get();
}

Object* Closure::eval(Environment&) {
  return this;
}

void Closure::mark() {
  Object::mark();
  lambda->mark();
}

bool Closure::isClosure() const {
  return true;
}

std::string Closure::toString() const {
  return "CLOSURE";
}

}
