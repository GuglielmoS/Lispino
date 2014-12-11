#include "Eqv.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

bool Eqv::hasExactArguments() const {
  return false;
}

std::uint32_t Eqv::getRequiredArguments() const {
  return 2;
}

std::string Eqv::getName() const {
  return "eqv?";
}

Object* Eqv::apply(std::vector<Object*>& args, std::shared_ptr<Environment>) throw(errors::RuntimeError) {
  for (unsigned int i = 0; i < args.size()-1; i++) {
    if (!args[i]->eqv(args[i+1]))
      return VM::getAllocator().createBoolean(false);
  }

  return VM::getAllocator().createBoolean(true);
}
}
}
