#ifndef LISPINO_BUILTINS_BUILTINFUNCTION_H_
#define LISPINO_BUILTINS_BUILTINFUNCTION_H_

#include <vector>

#include "../Object.h"

namespace Lispino {

namespace Builtins {

class BuiltinFunction : public Object {
 public:
  virtual Object* apply(std::vector<Object*>& args, Environment* env) throw (Errors::RuntimeError) = 0;

  Object* eval(Environment* env) throw (Errors::RuntimeError) override;

  bool isBuiltinFunction() const override;

  std::string toString() const override;
};

}

}

#endif // LISPINO_BUILTINS_BUILTINFUNCTION_H_
