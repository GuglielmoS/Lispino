#include "Cons.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

std::uint32_t Cons::getRequiredArguments() const {
  return 2;
}

std::string Cons::getName() const {
  return "cons";
}

Object* Cons::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(errors::RuntimeError) {
  return VM::getAllocator().createList(eval(args[0], env), eval(args[1], env));
}
}
}
