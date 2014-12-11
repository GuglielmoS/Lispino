#include "Div.h"

#include "../VM.h"

namespace lispino {

namespace builtins {

bool Div::hasExactArguments() const {
  return false;
}

std::uint32_t Div::getRequiredArguments() const {
  return 2;
}

std::string Div::getName() const {
  return "/";
}

Object* Div::apply(std::vector<Object*>& args, std::shared_ptr<Environment>) throw(errors::RuntimeError) {
  // check that the first argument is a number
  check(args[0], {ObjectType::INT_NUMBER, ObjectType::FLOAT_NUMBER});

  Number *result = static_cast<Number*>(args[0]);
  for (unsigned int i = 1; i < args.size(); i++) {
    // check that the current object is a number
    check(args[i], {ObjectType::INT_NUMBER, ObjectType::FLOAT_NUMBER});

    // add it to the accumulator
    result = result->div(static_cast<Number*>(args[i]));
  }

  return result;
}
}
}
