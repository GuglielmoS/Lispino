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

Object* Cons::apply(std::vector<Object*>& args, std::shared_ptr<Environment>) throw(errors::RuntimeError) {
  return VM::getAllocator().createList(args[0], args[1]);
}
}
}
