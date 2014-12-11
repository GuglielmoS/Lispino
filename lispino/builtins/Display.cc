#include "Display.h"

#include <iostream>
#include <sstream>
#include <string>

#include "../VM.h"

namespace lispino {

namespace builtins {

bool Display::hasExactArguments() const {
  return false;
}

std::uint32_t Display::getRequiredArguments() const {
  return 1;
}

std::string Display::getName() const {
  return "display";
}

Object* Display::apply(std::vector<Object*>& args, std::shared_ptr<Environment>) throw(errors::RuntimeError) {
  std::stringstream buf;
  std::string current_value;

  for (auto& current_arg : args) {
    if (current_arg->isString())
      current_value = static_cast<String*>(current_arg)->getValue();
    else
      current_value = current_arg->toString();

    std::cout << current_value;
    buf << current_value;
  }

  return VM::getAllocator().createString(buf.str());
}
}
}
