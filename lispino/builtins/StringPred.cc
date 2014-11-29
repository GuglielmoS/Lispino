#include "StringPred.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

std::uint32_t StringPred::getRequiredArguments() const {
  return 1;
}

std::string StringPred::getName() const {
  return "string?";
}

Object* StringPred::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(errors::RuntimeError) {
  Object* result = eval(args[0], env);
  return VM::getAllocator().createBoolean(result->isString());
}
}
}
