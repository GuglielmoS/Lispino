#ifndef LISPINO_BUILTINS_PROMISEPRED_H_
#define LISPINO_BUILTINS_PROMISEPRED_H_

#include "BuiltinFunction.h"

namespace lispino {

namespace builtins {

class PromisePred : public BuiltinFunction {
 public:
  std::uint32_t getRequiredArguments() const override;

  std::string getName() const override;

  Object* apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(errors::RuntimeError) override;
};
}
}

#endif  // LISPINO_BUILTINS_PROMISEPRED_H_
