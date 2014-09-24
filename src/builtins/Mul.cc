#include "Mul.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

bool Mul::hasExactArguments() const {
  return false;
}

std::uint32_t Mul::getRequiredArguments() const {
  return 1;
}
  
std::string Mul::getName() const {
  return "*";
}

Object* Mul::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  Object* result = args[0]->eval(env);
  for (unsigned int i = 1; i < args.size(); i++)
    result = result->mul(args[i]->eval(env));

  return result;
}

}

}
