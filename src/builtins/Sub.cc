#include "Sub.h"

#include "../VM.h"
#include "../IntNumber.h"
#include "../FloatNumber.h"

namespace Lispino {

namespace Builtins {

std::uint32_t Sub::getRequiredArguments() const {
  return 1;
}
  
std::string Sub::getName() const {
  return "-";
}

Object* Sub::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  Object* result = args[0]->eval(env);
  for (unsigned int i = 1; i < args.size(); i++)
    result = result->sub(args[i]->eval(env));

  if (args.size() == 1)
    return result->negate();
  else
    return result;
}

}

}
