#include "Mul.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

Object* Mul::apply(std::vector<Object*>& args, Environment& env) {
  if (args.size() <= 1)
    throw std::runtime_error("*: wrong number of arguments!");

  Object* result = args[0]->eval(env);
  for (unsigned int i = 1; i < args.size(); i++)
    result = result->mul(args[i]->eval(env));

  return result;
}

}

}