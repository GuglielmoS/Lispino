#include "CharPred.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

std::uint32_t CharPred::getRequiredArguments() const {
  return 1;
}

std::string CharPred::getName() const {
  return "char?";
}

Object* CharPred::apply(std::vector<Object*>& args, std::shared_ptr<Environment>) throw(errors::RuntimeError) {
  return VM::getAllocator().createBoolean(args[0]->isCharacter());
}
}
}
