#include "Cons.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

std::uint32_t Cons::getRequiredArguments() const {
  return 2;
}

std::string Cons::getName() const {
  return "cons";
}

Object* Cons::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(Errors::RuntimeError) {
  return VM::getAllocator().createList(eval(args[0], env), eval(args[1], env));
}
}
}
