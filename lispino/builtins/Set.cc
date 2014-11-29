#include "Set.h"

#include "../VM.h"
#include "../Symbol.h"

namespace lispino {

namespace builtins {

std::uint32_t Set::getRequiredArguments() const {
  return 2;
}

std::string Set::getName() const {
  return "set!";
}

Object* Set::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw(errors::RuntimeError) {
  check(args[0], ObjectType::SYMBOL);

  // evaluate the expression to assing
  Object *result = eval(args[1], env);

  // update the given symbol
  return env->update(static_cast<Symbol*>(args[0]), result);
}
}
}
