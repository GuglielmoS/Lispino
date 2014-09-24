#include "CharPred.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

std::uint32_t CharPred::getRequiredArguments() const {
  return 1;
}
  
std::string CharPred::getName() const {
  return "char?";
}

Object* CharPred::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  Object* result = args[0]->eval(env);
  return VM::getAllocator().createBoolean(result->isCharacter());
}

}

}
