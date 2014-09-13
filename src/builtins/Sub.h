#ifndef LISPINO_BUILTINS_SUB_H_
#define LISPINO_BUILTINS_SUB_H_

#include "BuiltinFunction.h"

namespace Lispino {

namespace Builtins {

class Sub : public BuiltinFunction {
 public:
  Object* apply(std::vector<Object*>& args, Environment& env);
};

}

}

#endif // LISPINO_BUILTINS_SUB_H_