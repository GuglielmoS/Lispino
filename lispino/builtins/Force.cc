#include "Force.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

std::uint32_t Force::getRequiredArguments() const {
  return 1;
}

std::string Force::getName() const {
  return "force";
}

Object* Force::apply(std::vector<Object*>& args, std::shared_ptr<Environment>) throw(errors::RuntimeError) {
  // evaluate the first argument
  check(args[0], ObjectType::PROMISE);
  Promise *promise = static_cast<Promise*>(args[0]);

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
