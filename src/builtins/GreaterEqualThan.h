#ifndef LISPINO_BUILTINS_GREATEREQUALTHAN_H_
#define LISPINO_BUILTINS_GREATEREQUALTHAN_H_

#include "BuiltinFunction.h"

namespace Lispino {

namespace Builtins {

class GreaterEqualThan : public BuiltinFunction {
 public:
  Object* apply(std::vector<Object*>& args, Environment* env) throw (Errors::RuntimeError) override;
};

}

}

#endif // LISPINO_BUILTINS_GREATEREQUALTHAN_H_
