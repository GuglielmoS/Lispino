#include "LowerEqualThan.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

bool LowerEqualThan::hasExactArguments() const {
  return false;
}

std::uint32_t LowerEqualThan::getRequiredArguments() const {
  return 2;
}
  
std::string LowerEqualThan::getName() const {
  return "<=";
}

Object* LowerEqualThan::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  for (unsigned int i = 0; i < args.size()-1; i++) {
    if (args[i]->eval(env)->compare(args[i+1]->eval(env)) > 0)
      return VM::getAllocator().createBoolean(false);
  }

  return VM::getAllocator().createBoolean(true);
}

}

}
