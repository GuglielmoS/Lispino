#include "Div.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

std::uint32_t Div::getRequiredArguments() const {
  return 2;
}
  
std::string Div::getName() const {
  return "/";
}

Object* Div::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  Object* result = args[0]->eval(env);
  for (unsigned int i = 1; i < args.size(); i++)
    result = result->div(args[i]->eval(env));

  return result;
}

}

}
