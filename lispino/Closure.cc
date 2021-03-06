#include "Closure.h"

#include <sstream>

#include "VM.h"

namespace lispino {

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

std::shared_ptr<Environment> Closure::getEnv() const {
  return env;
}

std::string Closure::toString() const {
  std::stringstream buf;
  buf << "<#CLOSURE:" << this << ">";
  return buf.str();
}
}
