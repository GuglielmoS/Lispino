#include "Remainder.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

std::uint32_t Remainder::getRequiredArguments() const {
  return 2;
}
  
std::string Remainder::getName() const {
  return "remainder";
}


Object* Remainder::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  Object* result = args[0]->eval(env);
  for (unsigned int i = 1; i < args.size(); i++)
    result = result->remainder(args[i]->eval(env));

  return result;
}

}

}
