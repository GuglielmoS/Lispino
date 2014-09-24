#include "NumberPred.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

std::uint32_t NumberPred::getRequiredArguments() const {
  return 1;
}
  
std::string NumberPred::getName() const {
  return "number?";
}

Object* NumberPred::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  Object* result = args[0]->eval(env);
  return VM::getAllocator().createBoolean(result->isIntNumber() || result->isFloatNumber());
}

}

}
