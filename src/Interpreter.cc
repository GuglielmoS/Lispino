#include "Interpreter.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>

#include "VM.h"
#include "Parser.h"
#include "errors/CompileError.h"
#include "errors/RuntimeError.h"

namespace Lispino {

Interpreter::Interpreter() : evaluator(VM::getEvaluator()) {
  /* DO NOTHING */ 
}

void Interpreter::init() {
  // try to load the standard library
  execute(LIB_DIR + "/" + STDLIB_FILE);

  // try to load the unit testing library
  execute(LIB_DIR + "/" + TESTLIB_FILE);
}

int Interpreter::repl() {
  bool terminated = false;


  // Read - Eval - Print - Loop
  while (not terminated) {
    std::string input_expr;

    // gets the expression
    std::cout << "> ";
    std::getline(std::cin, input_expr);

    // evaluates the expression
    if (input_expr == "quit") {
      terminated = true;
    } else if (input_expr != "") {
      std::stringstream stream(input_expr);

      // try to parse and evaluate the given expression
      try {
        auto expr = Parser(stream).parse();
        auto result = evaluator.eval(expr);
        std::cout << result->toString() << std::endl;
      } catch (Errors::CompileError& error) {
        std::cout << error.getMessage() << std::endl; 
      } catch (Errors::RuntimeError& error) {
        std::cout << error.getMessage() << std::endl;
      }

      // perform a garbage collection cycle
      VM::getMemory().cleanup();
    }
  }

  return 0;
}

int Interpreter::execute(std::string filename) {
  std::ifstream input_stream(filename);

  if (input_stream.is_open()) {
    Parser parser(input_stream);

    Object *current_expr = nullptr;
    while ((current_expr = parser.parseExpr()) != nullptr) {
      // evaluate the current expression
      evaluator.eval(current_expr);

      // run the garbage collector
      VM::getMemory().cleanup();
    }

    input_stream.close();

    return 0;
  }
  else {
    std::cerr << "File not found: " << filename << std::endl;
    return 1;
  }
}

}
