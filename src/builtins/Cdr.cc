#include "Cdr.h"

#include "../VM.h"

namespace Lispino {

namespace Builtins {

std::uint32_t Cdr::getRequiredArguments() const {
  return 1;
}
  
std::string Cdr::getName() const {
  return "cdr";
}

Object* Cdr::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  Object *value = eval(args[0], env);
  check(value, ObjectType::LIST);

  return static_cast<List*>(value)->getRest();
}

}

}
