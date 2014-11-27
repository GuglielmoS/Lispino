#include "Equal.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

bool Equal::hasExactArguments() const {
  return false;
}

std::uint32_t Equal::getRequiredArguments() const {
  return 2;
}

std::string Equal::getName() const {
  return "equal?";
}

Object* Equal::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(Errors::RuntimeError) {
  for (unsigned int i = 0; i < args.size()-1; i++) {
    Object *cur_obj = eval(args[i], env);
    Object *next_obj = eval(args[i+1], env);
    if (!cur_obj->equal(next_obj))
      return VM::getAllocator().createBoolean(false);
  }

  return VM::getAllocator().createBoolean(true);
}
}
}
