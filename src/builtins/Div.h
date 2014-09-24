#ifndef LISPINO_BUILTINS_DIV_H_
#define LISPINO_BUILTINS_DIV_H_

#include "BuiltinFunction.h"

namespace Lispino {

namespace Builtins {

class Div : public BuiltinFunction {
 public:
  bool hasExactArguments() const override;

  std::uint32_t getRequiredArguments() const override;
  
  std::string getName() const override;

  Object* apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) override;
};

}

}

#endif // LISPINO_BUILTINS_DIV_H_
