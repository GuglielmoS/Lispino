#include "Div.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

Object* Div::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  if (args.size() <= 1)
    throw Errors::RuntimeError(/*"div: wrong number of arguments"*/);

  Object* result = args[0]->eval(env);
  for (unsigned int i = 1; i < args.size(); i++)
    result = result->div(args[i]->eval(env));

  return result;
}

}

}
