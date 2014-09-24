#include "And.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

bool And::hasExactArguments() const {
  return false;
}

std::uint32_t And::getRequiredArguments() const {
  return 2;
}
  
std::string And::getName() const {
  return "and";
}

Object* And::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  for (auto& arg : args) {
    if (arg->eval(env)->isFalse())
      return VM::getAllocator().createBoolean(false);
  }

  return VM::getAllocator().createBoolean(true);
}

}

}
