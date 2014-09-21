#include "Closure.h"
#include "VM.h"

namespace Lispino {

Closure::Closure() : Object(ObjectType::CLOSURE), lambda(nullptr), env(nullptr) {
  /* DO NOTHING */
}

void Closure::setLambda(Lambda *lambda) {
  this->lambda = lambda;
}

void Closure::setEnv(std::shared_ptr<Environment> env) {
  this->env = env;
}

Lambda* Closure::getLambda() {
  return lambda;
}

std::shared_ptr<Environment> Closure::getEnv() {
  return env;
}

Object* Closure::eval(Environment*) throw (Errors::RuntimeError) {
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
