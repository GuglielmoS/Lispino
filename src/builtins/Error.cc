#include "Error.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

std::uint32_t Error::getRequiredArguments() const {
  return 1;
}
  
std::string Error::getName() const {
  return "error";
}

Object* Error::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  Object *error_message = eval(args[0], env);

  // check that the argument given is a String
  check(error_message, ObjectType::STRING);

  // throw the specified runtime error
  throw Errors::RuntimeError("USER-ERROR: " + error_message->toString()); 
}

}

}
