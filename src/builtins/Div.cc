#include "Div.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

bool Div::hasExactArguments() const {
  return false;
}

std::uint32_t Div::getRequiredArguments() const {
  return 2;
}
  
std::string Div::getName() const {
  return "/";
}

Object* Div::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  // evaluate the first argument
  Object* first_arg = args[0]->eval(env);

  // check that the first argument is a number
  if (!first_arg->isNumber())
    throw Errors::RuntimeError("+: expected number, found something else");

  Number *result = static_cast<Number*>(first_arg);
  for (unsigned int i = 1; i < args.size(); i++) {
    Object *cur_obj = args[i]->eval(env);

    // check that the current object is a number
    if (!cur_obj->isNumber())
      throw Errors::RuntimeError("+: expected number, found something else");

    // add it to the accumulator
    result = result->div(static_cast<Number*>(cur_obj));
  }

  return result;
}

}

}
