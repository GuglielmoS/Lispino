#include "Cdr.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

Object* Cdr::apply(std::vector<Object*>& args, Environment* env) throw (Errors::RuntimeError) {
  if (args.size() != 1)
    throw Errors::RuntimeError(/*"cdr: wrong number of arguments"*/);

  Object *value = args[0]->eval(env);
  if (!value->isList())
    throw Errors::RuntimeError(/*"cdr: invalid argument"*/);

  return static_cast<List*>(value)->getRest();
}

}

}
