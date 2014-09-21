#include "Display.h"

#include <iostream>
#include <sstream>
#include <string>

#include "../VM.h"

namespace Lispino {

namespace Builtins {

std::uint32_t Display::getRequiredArguments() const {
  return 1;
}
  
std::string Display::getName() const {
  return "display";
}

Object* Display::apply(std::vector<Object*>& args, std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  std::stringstream buf;
  std::string current_value;
  Object *current_object;

  for (auto& current_arg : args) {
    current_object = current_arg->eval(env);

    if (current_object->isString())
      current_value = static_cast<String*>(current_object)->getValue();
    else
      current_value = current_object->toString();

    std::cout << current_value;
    buf << current_value;
  }

  return VM::getAllocator().createString(buf.str());
}

}

}
