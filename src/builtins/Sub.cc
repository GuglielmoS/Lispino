#include "Sub.h"

#include "../VM.h"
#include "../IntNumber.h"
#include "../FloatNumber.h"

namespace Lispino {

namespace Builtins {

Object* Sub::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  if (args.size() == 0)
    throw Errors::RuntimeError(/*"-: wrong number of arguments"*/);

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
