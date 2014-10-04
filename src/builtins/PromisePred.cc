#include "PromisePred.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

std::uint32_t PromisePred::getRequiredArguments() const {
  return 1;
}
  
std::string PromisePred::getName() const {
  return "promise?";
}

Object* PromisePred::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  Object* result = args[0]->eval(env);
  return VM::getAllocator().createBoolean(result->isPromise());
}

}

}
