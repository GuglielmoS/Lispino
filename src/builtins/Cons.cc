#include "Cons.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

std::uint32_t Cons::getRequiredArguments() const {
  return 2;
}
  
std::string Cons::getName() const {
  return "cons";
}

Object* Cons::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  return VM::getAllocator().createList(args[0]->eval(env), args[1]->eval(env));
}

}

}
