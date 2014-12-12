#include "Apply.h"

#include "../VM.h"
#include "../utils/List.h"
#include "../errors/RuntimeError.h"

namespace lispino {

namespace builtins {

std::uint32_t Apply::getRequiredArguments() const {
  return 2;
}

std::string Apply::getName() const {
  return "apply";
}

Object* Apply::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(errors::RuntimeError) {
  // check if the procedure is callable
  check(args[0], {ObjectType::LAMBDA,
                  ObjectType::CLOSURE,
                  ObjectType::BUILTIN_FUNCTION});

  // check that the arguments are provided as a list
  check(args[1], ObjectType::LIST);

  // evaluate the application of the procedure on the given arguments
  // (the last argument is used for indicating 'eval' to not re-evaluate 
  //  the procedure's arguments)
  return eval(VM::getAllocator().createList(args[0], args[1]), env, false);
}
}
}
