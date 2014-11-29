#ifndef LISPINO_BUILTINS_BUILTINFUNCTION_H_
#define LISPINO_BUILTINS_BUILTINFUNCTION_H_

#include <cstdint>

#include <vector>
#include <memory>

#include "../Object.h"

namespace lispino {

namespace builtins {

class BuiltinFunction : public Object {
 public:
  BuiltinFunction() : Object(ObjectType::BUILTIN_FUNCTION) {}

  virtual bool hasExactArguments() const;

  virtual std::uint32_t getRequiredArguments() const = 0;

  virtual std::string getName() const = 0;

  virtual Object* apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(errors::RuntimeError) = 0;

  std::string toString() const override;

 protected:
  void check(Object *object, ObjectType expected_type) const throw(errors::RuntimeError);
  void check(Object *object, std::initializer_list<ObjectType> expected_types) const throw(errors::RuntimeError);
};
}
}

#endif  // LISPINO_BUILTINS_BUILTINFUNCTION_H_
