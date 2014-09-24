#include "ProcedurePred.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

std::uint32_t ProcedurePred::getRequiredArguments() const {
  return 1;
}
  
std::string ProcedurePred::getName() const {
  return "procedure?";
}

Object* ProcedurePred::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  Object* result = args[0]->eval(env);
  return VM::getAllocator().createBoolean(result->isLambda() || result->isClosure());
}

}

}
