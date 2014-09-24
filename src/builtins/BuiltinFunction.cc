#include "BuiltinFunction.h"

namespace Lispino {

namespace Builtins {

bool BuiltinFunction::hasExactArguments() const {
  return true;
}

std::string BuiltinFunction::toString() const {
  return "#<BUILTIN-FUNCTION:" + getName() + ">";
}

}

}
