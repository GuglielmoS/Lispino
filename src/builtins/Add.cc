#include "Add.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

std::uint32_t Add::getRequiredArguments() const {
  return 1;
}
  
std::string Add::getName() const {
  return "+";
}

Object* Add::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  Object* result = args[0]->eval(env);
  for (unsigned int i = 1; i < args.size(); i++)
    result = result->add(args[i]->eval(env));

  return result;
}

}

}
