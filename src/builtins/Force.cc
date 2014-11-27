#include "Force.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

std::uint32_t Force::getRequiredArguments() const {
  return 1;
}

std::string Force::getName() const {
  return "force";
}

Object* Force::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(Errors::RuntimeError) {
  // evaluate the first argument
  Object *first_arg = eval(args[0], env);
  check(first_arg, ObjectType::PROMISE);

  Promise *promise = static_cast<Promise*>(first_arg);

  // check if the promise has been already evaluated
  if (promise->hasCachedResult()) {
    return promise->getCachedResult();
  } else {
    // evaluate the promise code in its original environment
    Object *result = eval(promise->getBody(), promise->getEnv());
    promise->setCachedResult(result);
    return result;
  }
}
}
}
