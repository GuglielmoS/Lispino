#include "BooleanPred.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

std::uint32_t BooleanPred::getRequiredArguments() const {
  return 1;
}
  
std::string BooleanPred::getName() const {
  return "boolean?";
}

Object* BooleanPred::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  Object* result = args[0]->eval(env);
  return VM::getAllocator().createBoolean(result->isBoolean());
}

}

}
