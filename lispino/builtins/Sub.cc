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

Object* Sub::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(errors::RuntimeError) {
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
    result = result->sub(static_cast<Number*>(cur_obj));
  }

  if (args.size() == 1)
    return result->negate();
  else
    return result;
}
}
}
