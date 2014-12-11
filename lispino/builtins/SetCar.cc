#include "SetCar.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

std::uint32_t SetCar::getRequiredArguments() const {
  return 2;
}

std::string SetCar::getName() const {
  return "set-car!";
}

Object* SetCar::apply(std::vector<Object*>& args, std::shared_ptr<Environment>) throw(errors::RuntimeError) {
  // check that the first argument is a list
  check(args[0], ObjectType::LIST);
  List *list = static_cast<List*>(args[0]);

  // update the CAR of the given list
  list->setFirst(args[1]);

  return args[1];
}
}
}
