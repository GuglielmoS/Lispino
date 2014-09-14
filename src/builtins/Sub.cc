#include "Sub.h"

#include "../VM.h"
#include "../IntNumber.h"
#include "../FloatNumber.h"

namespace Lispino {

namespace Builtins {

Object* Sub::apply(std::vector<Object*>& args, Environment* env) {
  if (args.size() == 0)
    throw std::runtime_error("-: wrong number of arguments!");

  Object* result = args[0]->eval(env);
  for (unsigned int i = 1; i < args.size(); i++)
    result = result->sub(args[i]->eval(env));

  if (args.size() == 1)
    return result->negate();
  else
    return result;
}

}

}
