#include "SetCdr.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

std::uint32_t SetCdr::getRequiredArguments() const {
  return 2;
}
  
std::string SetCdr::getName() const {
  return "set-cdr!";
}

Object* SetCdr::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  Object *first_arg = eval(args[0], env);

  // check that the first argument is a list
  check(first_arg, ObjectType::LIST);
  List *list = static_cast<List*>(first_arg);

  // evaluate the expression to assign
  Object *result = eval(args[1], env);

  // update the CDR of the given list
  list->setRest(result);

  return result;
}

}

}
