#include "Car.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

Object* Car::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  if (args.size() != 1)
    throw Errors::RuntimeError(/*"car: wrong number of arguments"*/);

  Object *value = args[0]->eval(env);
  if (!value->isList())
    throw Errors::RuntimeError(/*"car: invalid argument"*/);

  return static_cast<List*>(value)->getFirst();
}

}

}
