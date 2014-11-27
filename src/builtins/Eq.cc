#include "Eq.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

bool Eq::hasExactArguments() const {
  return false;
}

std::uint32_t Eq::getRequiredArguments() const {
  return 2;
}

std::string Eq::getName() const {
  return "eq?";
}

Object* Eq::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(Errors::RuntimeError) {
  for (unsigned int i = 0; i < args.size()-1; i++) {
    auto cur_obj = eval(args[i], env);
    auto next_obj = eval(args[i+1], env);

    if (!cur_obj->eq(next_obj))
      return VM::getAllocator().createBoolean(false);
  }

  return VM::getAllocator().createBoolean(true);
}
}
}
