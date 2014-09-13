#ifndef LISPINO_BUILTINS_NEWLINE_H_
#define LISPINO_BUILTINS_NEWLINE_H_

#include "BuiltinFunction.h"

namespace Lispino {

namespace Builtins {

class Newline : public BuiltinFunction {
 public:
  Object* apply(std::vector<Object*>& args, Environment& env);
};

}

}

#endif // LISPINO_BUILTINS_NEWLINE_H_
