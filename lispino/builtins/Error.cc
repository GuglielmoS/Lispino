#include "Error.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

std::uint32_t Error::getRequiredArguments() const {
  return 1;
}

std::string Error::getName() const {
  return "error";
}

Object* Error::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(errors::RuntimeError) {
  Object *error_message = eval(args[0], env);

  // check that the argument given is a String
  check(error_message, ObjectType::STRING);

  // throw the specified runtime error
  throw errors::RuntimeError("USER-ERROR: " + error_message->toString());
}
}
}
