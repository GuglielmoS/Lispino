#include "Mul.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

bool Mul::hasExactArguments() const {
  return false;
}

std::uint32_t Mul::getRequiredArguments() const {
  return 1;
}

std::string Mul::getName() const {
  return "*";
}

Object* Mul::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(errors::RuntimeError) {
  // evaluate the first argument
  Object* first_arg = eval(args[0], env);

  // check that the first argument is a number
  check(first_arg, {ObjectType::INT_NUMBER, ObjectType::FLOAT_NUMBER});

  Number *result = static_cast<Number*>(first_arg);
  for (unsigned int i = 1; i < args.size(); i++) {
    Object *cur_obj = eval(args[i], env);

    // check that the current object is a number
    check(cur_obj, {ObjectType::INT_NUMBER, ObjectType::FLOAT_NUMBER});

    // add it to the accumulator
    result = result->mul(static_cast<Number*>(cur_obj));
  }

  return result;
}
}
}
