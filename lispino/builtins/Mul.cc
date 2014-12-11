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

Object* Mul::apply(std::vector<Object*>& args, std::shared_ptr<Environment>) throw(errors::RuntimeError) {
  // check that the first argument is a number
  check(args[0], {ObjectType::INT_NUMBER, ObjectType::FLOAT_NUMBER});

  Number *result = static_cast<Number*>(args[0]);
  for (unsigned int i = 1; i < args.size(); i++) {
    // check that the current object is a number
    check(args[i], {ObjectType::INT_NUMBER, ObjectType::FLOAT_NUMBER});

    // add it to the accumulator
    result = result->mul(static_cast<Number*>(args[i]));
  }

  return result;
}
}
}
