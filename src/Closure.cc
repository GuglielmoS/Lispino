#include "Closure.h"
#include "VM.h"

namespace Lispino {

Closure::Closure() : lambda(nullptr), env(nullptr) {
  /* DO NOTHING */
}

Closure::Closure(Lambda *lambda, Environment *parent_env)
    : lambda(lambda), 
      env(new Environment(parent_env)) {
  /* DO NOTHING */    
}

void Closure::setLambda(Lambda *lambda) {
  this->lambda = lambda;
}

void Closure::setEnv(Environment *parent_env) {
  this->env.reset(new Environment(parent_env));
}

Environment* Closure::getEnv() {
  return env.get();
}

Object* Closure::eval(Environment& env) {
  return this;
}

Object* Closure::apply(std::vector<Object*>& actual_args) {
  std::vector<std::string> formal_args = lambda->getArguments();

  if (formal_args.size() != actual_args.size())
    throw std::runtime_error("Invalid function call, wrong number of arguments");

  for (unsigned int i = 0; i < formal_args.size(); i++)
    env->put(VM::getAllocator().createSymbol(formal_args[i]), actual_args[i]);

  return lambda->getBody()->eval(*env);
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
