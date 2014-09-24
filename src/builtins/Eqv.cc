#include "Eqv.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

bool Eqv::hasExactArguments() const {
  return false;
}

std::uint32_t Eqv::getRequiredArguments() const {
  return 2;
}
  
std::string Eqv::getName() const {
  return "eqv?";
}

Object* Eqv::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  for (unsigned int i = 0; i < args.size()-1; i++) {
    auto cur_obj = args[i]->eval(env);
    auto next_obj = args[i+1]->eval(env);

    if (!cur_obj->eqv(next_obj))
      return VM::getAllocator().createBoolean(false);
  }

  return VM::getAllocator().createBoolean(true);
}

}

}
