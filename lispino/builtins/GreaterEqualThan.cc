#include "GreaterEqualThan.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

bool GreaterEqualThan::hasExactArguments() const {
  return false;
}

std::uint32_t GreaterEqualThan::getRequiredArguments() const {
  return 2;
}

std::string GreaterEqualThan::getName() const {
  return ">=";
}

Object* GreaterEqualThan::apply(std::vector<Object*>& args, std::shared_ptr<Environment>) throw(errors::RuntimeError) {
  for (unsigned int i = 0; i < args.size()-1; i++) {
    if (args[i]->compare(args[i+1]) < 0)
      return VM::getAllocator().createBoolean(false);
  }

  return VM::getAllocator().createBoolean(true);
}
}
}
