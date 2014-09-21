#ifndef LISPINO_BUILTINS_DISPLAY_H_
#define LISPINO_BUILTINS_DISPLAY_H_

#include <vector>

#include "BuiltinFunction.h"

namespace Lispino {

namespace Builtins {

class Display : public BuiltinFunction {
 public:
  Object* apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) override;
};

}

}

#endif // LISPINO_BUILTINS_DISPLAY_H_
