#include "Car.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

std::uint32_t Car::getRequiredArguments() const {
  return 1;
}

std::string Car::getName() const {
  return "car";
}

Object* Car::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(errors::RuntimeError) {
  Object *value = eval(args[0], env);
  check(value, ObjectType::LIST);

  return static_cast<List*>(value)->getFirst();
}
}
}
