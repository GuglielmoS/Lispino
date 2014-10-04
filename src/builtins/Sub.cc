#include "Sub.h"

#include "../VM.h"
#include "../IntNumber.h"
#include "../FloatNumber.h"

namespace Lispino {

namespace Builtins {

bool Sub::hasExactArguments() const {
  return false;
}

std::uint32_t Sub::getRequiredArguments() const {
  return 1;
}
  
std::string Sub::getName() const {
  return "-";
}

Object* Sub::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  // evaluate the first argument
  Object* first_arg = args[0]->eval(env);

  // check that the first argument is a number
  if (!first_arg->isNumber())
    throw Errors::RuntimeError("-: expected number, found something else");

  Number *result = static_cast<Number*>(first_arg);
  for (unsigned int i = 1; i < args.size(); i++) {
    Object *cur_obj = args[i]->eval(env);

    // check that the current object is a number
    if (!cur_obj->isNumber())
      throw Errors::RuntimeError("+: expected number, found something else");

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
