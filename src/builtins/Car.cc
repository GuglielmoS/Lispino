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

Object* Car::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(Errors::RuntimeError) {
  Object *value = eval(args[0], env);
  check(value, ObjectType::LIST);

  return static_cast<List*>(value)->getFirst();
}
}
}
