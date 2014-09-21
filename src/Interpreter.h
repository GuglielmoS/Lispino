#ifndef LISPINO_INTERPRETER_H_
#define LISPINO_INTERPRETER_H_

#include <string>

namespace Lispino {

class Evaluator;

const std::string LIB_DIR = "lib";
const std::string STDLIB_FILE = "std.scm";
const std::string TESTLIB_FILE = "unittest.scm";

class Interpreter {
 public:
  Interpreter();

  void init();

  int repl();

  int execute(std::string filename);

 private:
  Evaluator& evaluator;
};

}

#endif // LISPINO_INTERPRETER_H_
