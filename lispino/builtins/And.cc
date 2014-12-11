#include "And.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

And::And() : BuiltinFunction(true) {
  /* DO NOTHING */
}

bool And::hasExactArguments() const {
  return false;
}

std::uint32_t And::getRequiredArguments() const {
  return 2;
}

std::string And::getName() const {
  return "and";
}

Object* And::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(errors::RuntimeError) {
  for (auto& arg : args) {
    if (eval(arg, env)->isFalse())
      return VM::getAllocator().createBoolean(false);
  }

  return VM::getAllocator().createBoolean(true);
}
}
}
