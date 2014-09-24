#include "SymbolPred.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

std::uint32_t SymbolPred::getRequiredArguments() const {
  return 1;
}
  
std::string SymbolPred::getName() const {
  return "symbol?";
}

Object* SymbolPred::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  Object* result = args[0]->eval(env);
  return VM::getAllocator().createBoolean(result->isSymbol());
}

}

}
