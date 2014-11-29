#include "NumberPred.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

std::uint32_t NumberPred::getRequiredArguments() const {
  return 1;
}

std::string NumberPred::getName() const {
  return "number?";
}

Object* NumberPred::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(errors::RuntimeError) {
  Object* result = eval(args[0], env);
  return VM::getAllocator().createBoolean(result->isNumber());
}
}
}
