#include "BuiltinFunction.h"

namespace Lispino {
    Object* BuiltinFunction::eval(Environment& env) {
        return this;
    }

    bool BuiltinFunction::isBuiltinFunction() const {
        return true;
    }

    std::string BuiltinFunction::toString() const {
        return "BUILTIN-FUNCTION";
    }
}
