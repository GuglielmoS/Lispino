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

Object* BooleanPred::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(errors::RuntimeError) {
  Object* result = eval(args[0], env);
  return VM::getAllocator().createBoolean(result->isBoolean());
}
}
}
