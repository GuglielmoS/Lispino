#ifndef LISPINO_BUILTINS_AND_H_
#define LISPINO_BUILTINS_AND_H_

#include "BuiltinFunction.h"

namespace lispino {

namespace builtins {

class And : public BuiltinFunction {
 public:
  bool hasExactArguments() const override;

  std::uint32_t getRequiredArguments() const override;

  std::string getName() const override;

  Object* apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(errors::RuntimeError) override;
};
}
}

#endif // LISPINO_BUILTINS_AND_H_
