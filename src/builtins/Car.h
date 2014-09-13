#ifndef LISPINO_BUILTINS_CAR_H_
#define LISPINO_BUILTINS_CAR_H_

#include "BuiltinFunction.h"

namespace Lispino {

namespace Builtins {

class Car : public BuiltinFunction {
 public:
  Object* apply(std::vector<Object*>& args, Environment& env);
};

}

}

#endif // LISPINO_BUILTINS_CAR_H_
