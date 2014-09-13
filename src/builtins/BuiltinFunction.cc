#include "BuiltinFunction.h"

namespace Lispino {

namespace Builtins {

Object* BuiltinFunction::eval(Environment&) {
  return this;
}

bool BuiltinFunction::isBuiltinFunction() const {
  return true;
}

std::string BuiltinFunction::toString() const {
  return "BUILTIN-FUNCTION";
}

}

}
