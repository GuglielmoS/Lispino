#ifndef LISPINO_BUILTINS_BUILTINFUNCTION_H_
#define LISPINO_BUILTINS_BUILTINFUNCTION_H_

#include <vector>
#include <memory>

#include "../Object.h"

namespace Lispino {

namespace Builtins {

class BuiltinFunction : public Object {
 public:
  BuiltinFunction() : Object(ObjectType::BUILTIN_FUNCTION) {}

  virtual Object* apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) = 0;

  std::string toString() const override;
};

}

}

#endif // LISPINO_BUILTINS_BUILTINFUNCTION_H_
