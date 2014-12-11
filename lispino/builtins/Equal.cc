#include "Equal.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

bool Equal::hasExactArguments() const {
  return false;
}

std::uint32_t Equal::getRequiredArguments() const {
  return 2;
}

std::string Equal::getName() const {
  return "equal?";
}

Object* Equal::apply(std::vector<Object*>& args, std::shared_ptr<Environment>) throw(errors::RuntimeError) {
  for (unsigned int i = 0; i < args.size()-1; i++) {
    if (!args[i]->equal(args[i+1]))
      return VM::getAllocator().createBoolean(false);
  }

  return VM::getAllocator().createBoolean(true);
}
}
}
