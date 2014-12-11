#include "NumberEqual.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

bool NumberEqual::hasExactArguments() const {
  return false;
}

std::uint32_t NumberEqual::getRequiredArguments() const {
  return 2;
}

std::string NumberEqual::getName() const {
  return "=";
}

Object* NumberEqual::apply(std::vector<Object*>& args, std::shared_ptr<Environment>) throw(errors::RuntimeError) {
  for (unsigned int i = 0; i < args.size()-1; i++) {
    if (args[i]->compare(args[i+1]) != 0)
      return VM::getAllocator().createBoolean(false);
  }

  return VM::getAllocator().createBoolean(true);
}
}
}
