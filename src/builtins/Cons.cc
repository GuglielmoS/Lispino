#include "Cons.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

Object* Cons::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  if (args.size() != 2)
    throw Errors::RuntimeError(/*"cons: wrong number of arguments"*/);

  return VM::getAllocator().createList(args[0]->eval(env), args[1]->eval(env));
}

}

}
