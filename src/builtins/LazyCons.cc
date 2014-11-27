#include "LazyCons.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

std::uint32_t LazyCons::getRequiredArguments() const {
  return 2;
}

std::string LazyCons::getName() const {
  return "lazy-cons";
}

Object* LazyCons::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(Errors::RuntimeError) {
  Object *first_element = eval(args[0], env);
  Promise *delayed_object = VM::getAllocator().createPromise(args[1], env);
  return VM::getAllocator().createList(first_element, delayed_object);
}
}
}
