#include "GreaterThan.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

Object* GreaterThan::apply(std::vector<Object*>& args, Environment* env) {
  if (args.size() <= 1)
    throw std::runtime_error(">: wrong number of arguments");

  for (unsigned int i = 0; i < args.size()-1; i++) {
    if (args[i]->eval(env)->compare(args[i+1]->eval(env)) <= 0)
      return VM::getAllocator().createBoolean(false);
  }

  return VM::getAllocator().createBoolean(true);
}

}

}
