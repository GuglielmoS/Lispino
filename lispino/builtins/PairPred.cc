#include "PairPred.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

std::uint32_t PairPred::getRequiredArguments() const {
  return 1;
}

std::string PairPred::getName() const {
  return "pair?";
}

Object* PairPred::apply(std::vector<Object*>& args, std::shared_ptr<Environment>) throw(errors::RuntimeError) {
  return VM::getAllocator().createBoolean(args[0]->isList());
}
}
}
