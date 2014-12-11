#include "SetCdr.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

std::uint32_t SetCdr::getRequiredArguments() const {
  return 2;
}

std::string SetCdr::getName() const {
  return "set-cdr!";
}

Object* SetCdr::apply(std::vector<Object*>& args, std::shared_ptr<Environment>) throw(errors::RuntimeError) {
  // check that the first argument is a list
  check(args[0], ObjectType::LIST);
  List *list = static_cast<List*>(args[0]);

  // update the CDR of the given list
  list->setRest(args[1]);

  return args[1];
}
}
}
