#include "PairPred.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

std::uint32_t PairPred::getRequiredArguments() const {
  return 1;
}
  
std::string PairPred::getName() const {
  return "pair?";
}

Object* PairPred::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  Object* result = eval(args[0], env);
  return VM::getAllocator().createBoolean(result->isList());
}

}

}
