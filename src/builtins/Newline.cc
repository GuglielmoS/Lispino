#include "Newline.h"

#include <iostream>

#include "../VM.h"

namespace Lispino {

namespace Builtins {

Object* Newline::apply(std::vector<Object*>& args, Environment&) {
  if (args.size() != 0)
    throw std::runtime_error("newline: wrong number of arguments!");

  // side effect
  std::cout << std::endl;

  return VM::getAllocator().createString("\n");
}

}

}
