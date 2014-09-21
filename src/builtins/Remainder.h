#ifndef LISPINO_BUILTINS_REMAINDER_H_
#define LISPINO_BUILTINS_REMAINDER_H_

#include "BuiltinFunction.h"

namespace Lispino {

namespace Builtins {

class Remainder : public BuiltinFunction {
 public:
  Object* apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) override;
};

}

}

#endif // LISPINO_BUILTINS_REMAINDER_H_
