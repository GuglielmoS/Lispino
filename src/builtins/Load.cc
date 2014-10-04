#include "Load.h"

#include <fstream>

#include "../VM.h"
#include "../String.h"
#include "../Parser.h"

namespace Lispino {

namespace Builtins {

std::uint32_t Load::getRequiredArguments() const {
  return 1;
}
  
std::string Load::getName() const {
  return "load";
}

Object* Load::apply(std::vector<Object*>& args, std::shared_ptr<Environment>) throw (Errors::RuntimeError) {
  // check that the given argument is a string
  check(args[0], ObjectType::STRING);

  // evaluate the code from the given file
  std::string filename = static_cast<String*>(args[0])->getValue();
  std::ifstream input_stream(filename);
  Evaluator &evaluator = VM::getEvaluator();

  if (input_stream.is_open()) {
    Parser parser(input_stream);

    Object *current_expr = nullptr;
    while ((current_expr = parser.parseExpr()) != nullptr) {
      evaluator.eval(current_expr);

      // run the garbage collector
      VM::getMemory().cleanup();
    }

    input_stream.close();
    
    return VM::getAllocator().createBoolean(true);
  } else {
    throw Errors::RuntimeError(getName() + ": can't open the given file");
  }
}

}

}
