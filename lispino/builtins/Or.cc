#include "Or.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

Or::Or() : BuiltinFunction(true) {
  /* DO NOTHING */
}

bool Or::hasExactArguments() const {
  return false;
}

std::uint32_t Or::getRequiredArguments() const {
  return 2;
}

std::string Or::getName() const {
  return "or";
}

Object* Or::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(errors::RuntimeError) {
  for (auto& arg : args) {
    if (eval(arg, env)->isTrue())
      return VM::getAllocator().createBoolean(true);
  }

  return VM::getAllocator().createBoolean(false);
}
}
}
