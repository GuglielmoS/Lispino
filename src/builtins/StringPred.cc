#include "StringPred.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

std::uint32_t StringPred::getRequiredArguments() const {
  return 1;
}
  
std::string StringPred::getName() const {
  return "string?";
}

Object* StringPred::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  Object* result = args[0]->eval(env);
  return VM::getAllocator().createBoolean(result->isString());
}

}

}
