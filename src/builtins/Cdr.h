#ifndef LISPINO_BUILTINS_CDR_H_
#define LISPINO_BUILTINS_CDR_H_

#include "BuiltinFunction.h"

namespace Lispino {

namespace Builtins {

class Cdr : public BuiltinFunction {
 public:
  Object* apply(std::vector<Object*>& args, Environment* env) throw (Errors::RuntimeError) override;
};

}

}

#endif // LISPINO_BUILTINS_CDR_H_
