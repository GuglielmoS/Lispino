#include "Set.h"

#include "../VM.h"
#include "../Symbol.h"

namespace Lispino {

namespace Builtins {

Object* Set::apply(std::vector<Object*>& args, Environment* env) throw (Errors::RuntimeError) {
  if (args.size() != 2)
    throw Errors::RuntimeError(/*"set!: wrong number of arguments"*/);

  if (!args[0]->isSymbol())
    throw Errors::RuntimeError(/*"set!: the first argument must be a symol"*/);

  // evaluate the expression to assing
  Object *result = args[1]->eval(env);

  // update the given symbol
  env->update(static_cast<Symbol*>(args[0]), result);

  return result;
}

}

}
