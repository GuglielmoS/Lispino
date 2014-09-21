#ifndef LISPINO_BUILTINS_MUL_H_
#define LISPINO_BUILTINS_MUL_H_

#include "BuiltinFunction.h"

namespace Lispino {

namespace Builtins {

class Mul : public BuiltinFunction {
 public:
  Object* apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) override;
};

}

}

#endif // LISPINO_BUILTINS_MUL_H_
