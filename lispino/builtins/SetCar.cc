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

Object* SetCar::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(errors::RuntimeError) {
  Object *first_arg = eval(args[0], env);

  // check that the first argument is a list
  check(first_arg, ObjectType::LIST);
  List *list = static_cast<List*>(first_arg);

  // evaluate the expression to assign
  Object *result = eval(args[1], env);

  // update the CAR of the given list
  list->setFirst(result);

  return result;
}
}
}
