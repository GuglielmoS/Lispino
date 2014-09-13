#ifndef LISPINO_BUILTINS_LOWEREQUALTHAN_H_
#define LISPINO_BUILTINS_LOWEREQUALTHAN_H_

#include "BuiltinFunction.h"

namespace Lispino {

namespace Builtins {

class LowerEqualThan : public BuiltinFunction {
 public:
  Object* apply(std::vector<Object*>& args, Environment& env);
};

}

}

#endif // LISPINO_BUILTINS_LOWEREQUALTHAN_H_
