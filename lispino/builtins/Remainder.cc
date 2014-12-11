#include "Remainder.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

bool Remainder::hasExactArguments() const {
  return false;
}

std::uint32_t Remainder::getRequiredArguments() const {
  return 2;
}

std::string Remainder::getName() const {
  return "remainder";
}

Object* Remainder::apply(std::vector<Object*>& args, std::shared_ptr<Environment>) throw(errors::RuntimeError) {
  // check that the first argument is a number
  check(args[0], {ObjectType::INT_NUMBER, ObjectType::FLOAT_NUMBER});

  Number *result = static_cast<Number*>(args[0]);
  for (unsigned int i = 1; i < args.size(); i++) {
    // check that the current object is a number
    check(args[i], {ObjectType::INT_NUMBER, ObjectType::FLOAT_NUMBER});

    // add it to the accumulator
    result = result->remainder(static_cast<Number*>(args[i]));
  }

  return result;
}
}
}
