#include "Remainder.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

Object* Remainder::apply(std::vector<Object*>& args, Environment* env) throw (Errors::RuntimeError) {
  if (args.size() <= 1)
    throw Errors::RuntimeError(/*"remainder: wrong number of arguments"*/);

  Object* result = args[0]->eval(env);
  for (unsigned int i = 1; i < args.size(); i++)
    result = result->remainder(args[i]->eval(env));

  return result;
}

}

}
