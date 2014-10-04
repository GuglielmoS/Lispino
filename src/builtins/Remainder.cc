#include "Remainder.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

bool Remainder::hasExactArguments() const {
  return false;
}

std::uint32_t Remainder::getRequiredArguments() const {
  return 2;
}
  
std::string Remainder::getName() const {
  return "remainder";
}


Object* Remainder::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  // evaluate the first argument
  Object* first_arg = args[0]->eval(env);

  // check that the first argument is a number
  check(first_arg, {ObjectType::INT_NUMBER, ObjectType::FLOAT_NUMBER});

  Number *result = static_cast<Number*>(first_arg);
  for (unsigned int i = 1; i < args.size(); i++) {
    Object *cur_obj = args[i]->eval(env);

    // check that the current object is a number
    check(cur_obj, {ObjectType::INT_NUMBER, ObjectType::FLOAT_NUMBER});

    // add it to the accumulator
    result = result->remainder(static_cast<Number*>(cur_obj));
  }

  return result;
}

}

}
