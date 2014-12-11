#include "ProcedurePred.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

std::uint32_t ProcedurePred::getRequiredArguments() const {
  return 1;
}

std::string ProcedurePred::getName() const {
  return "procedure?";
}

Object* ProcedurePred::apply(std::vector<Object*>& args, std::shared_ptr<Environment>) throw(errors::RuntimeError) {
  return VM::getAllocator().createBoolean(args[0]->isLambda() || args[0]->isClosure());
}
}
}
