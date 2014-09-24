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
  Object *error_message = args[0]->eval(env);

  // check that the argument given is a String
  if (!error_message->isString())
    throw Errors::RuntimeError("error: the message must be a string");

  // throw the specified runtime error
  throw Errors::RuntimeError("ERROR: " + error_message->toString()); 
}

}

}
