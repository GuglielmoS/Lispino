#include "Sub.h"

#include "../VM.h"
#include "../IntNumber.h"
#include "../FloatNumber.h"

namespace lispino {

namespace builtins {

bool Sub::hasExactArguments() const {
  return false;
}

std::uint32_t Sub::getRequiredArguments() const {
  return 1;
}

std::string Sub::getName() const {
  return "-";
}

Object* Sub::apply(std::vector<Object*>& args, std::shared_ptr<Environment>) throw(errors::RuntimeError) {
  // check that the first argument is a number
  check(args[0], {ObjectType::INT_NUMBER, ObjectType::FLOAT_NUMBER});

  Number *result = static_cast<Number*>(args[0]);
  for (unsigned int i = 1; i < args.size(); i++) {
    // check that the current object is a number
    check(args[i], {ObjectType::INT_NUMBER, ObjectType::FLOAT_NUMBER});

    // add it to the accumulator
    result = result->sub(static_cast<Number*>(args[i]));
  }

  if (args.size() == 1)
    return result->negate();
  else
    return result;
}
}
}
