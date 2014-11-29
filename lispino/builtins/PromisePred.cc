#include "PromisePred.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

std::uint32_t PromisePred::getRequiredArguments() const {
  return 1;
}

std::string PromisePred::getName() const {
  return "promise?";
}

Object* PromisePred::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(errors::RuntimeError) {
  Object* result = eval(args[0], env);
  return VM::getAllocator().createBoolean(result->isPromise());
}
}
}
