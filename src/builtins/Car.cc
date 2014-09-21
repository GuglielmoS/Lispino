#include "Car.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

std::uint32_t Car::getRequiredArguments() const {
  return 1;
}
  
std::string Car::getName() const {
  return "car";
}

Object* Car::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  Object *value = args[0]->eval(env);
  if (!value->isList())
    throw Errors::RuntimeError("car: invalid argument");

  return static_cast<List*>(value)->getFirst();
}

}

}
