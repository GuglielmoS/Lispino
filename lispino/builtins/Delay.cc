#include "Delay.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

Delay::Delay() : BuiltinFunction(true) {
  /* DO NOTHING */
}

std::uint32_t Delay::getRequiredArguments() const {
  return 1;
}

std::string Delay::getName() const {
  return "delay";
}

Object* Delay::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(errors::RuntimeError) {
  return VM::getAllocator().createPromise(args[0], env);
}
}
}
