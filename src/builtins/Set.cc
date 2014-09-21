#include "Set.h"

#include "../VM.h"
#include "../Symbol.h"

namespace Lispino {

namespace Builtins {

std::uint32_t Set::getRequiredArguments() const {
  return 2;
}
  
std::string Set::getName() const {
  return "set!";
}

Object* Set::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  if (!args[0]->isSymbol())
    throw Errors::RuntimeError("set!: the first argument must be a symbol");

  // evaluate the expression to assing
  Object *result = args[1]->eval(env);

  // update the given symbol
  env->update(static_cast<Symbol*>(args[0]), result);

  return result;
}

}

}
