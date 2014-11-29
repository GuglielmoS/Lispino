#include "SymbolPred.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

std::uint32_t SymbolPred::getRequiredArguments() const {
  return 1;
}

std::string SymbolPred::getName() const {
  return "symbol?";
}

Object* SymbolPred::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(errors::RuntimeError) {
  Object* result = eval(args[0], env);
  return VM::getAllocator().createBoolean(result->isSymbol());
}
}
}
