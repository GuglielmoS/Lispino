#include "Apply.h"

#include "../VM.h"
#include "../utils/List.h"
#include "../errors/RuntimeError.h"

namespace Lispino {

namespace Builtins {

std::uint32_t Apply::getRequiredArguments() const {
  return 2;
}
  
std::string Apply::getName() const {
  return "apply";
}

Object* Apply::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  // extract the procedure
  Object *procedure = args[0]->eval(env);

  // check if the procedure is callable
  check(procedure, {ObjectType::LAMBDA, 
                    ObjectType::CLOSURE,
                    ObjectType::BUILTIN_FUNCTION});

  // extract the arguments to apply
  Object *arguments_to_apply = args[1]->eval(env);

  // check that the arguments are provided as a list
  check(arguments_to_apply, ObjectType::LIST); 

  // evaluate the application of the procedure on the given arguments
  return VM::getAllocator().createList(procedure, arguments_to_apply)->eval(env); 
}

}

}
