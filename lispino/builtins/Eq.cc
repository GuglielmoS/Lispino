#include "Eq.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

bool Eq::hasExactArguments() const {
  return false;
}

std::uint32_t Eq::getRequiredArguments() const {
  return 2;
}

std::string Eq::getName() const {
  return "eq?";
}

Object* Eq::apply(std::vector<Object*>& args, std::shared_ptr<Environment>) throw(errors::RuntimeError) {
  for (unsigned int i = 0; i < args.size()-1; i++) {
    if (!args[i]->eq(args[i+1]))
      return VM::getAllocator().createBoolean(false);
  }

  return VM::getAllocator().createBoolean(true);
}
}
}
