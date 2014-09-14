#ifndef LISPINO_BUILTINS_CONS_H_
#define LISPINO_BUILTINS_CONS_H_

#include "BuiltinFunction.h"

namespace Lispino {

namespace Builtins {

class Cons : public BuiltinFunction {
 public:
  Object* apply(std::vector<Object*>& args, Environment* env);
};

}

}

#endif // LISPINO_BUILTINS_CONS_H_
