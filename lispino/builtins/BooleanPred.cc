#include "BooleanPred.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

std::uint32_t BooleanPred::getRequiredArguments() const {
  return 1;
}

std::string BooleanPred::getName() const {
  return "boolean?";
}

Object* BooleanPred::apply(std::vector<Object*>& args, std::shared_ptr<Environment>) throw(errors::RuntimeError) {
  return VM::getAllocator().createBoolean(args[0]->isBoolean());
}
}
}
