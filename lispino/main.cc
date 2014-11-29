#include "Interpreter.h"

#include <iostream>
#include <cstring>

int main(int argc, char *argv[]) {
  lispino::Interpreter interpreter;

  // initialize the interpreter
  interpreter.init();

  // launch the REPL or execute a given file
  if (argc == 2)
    return interpreter.execute(argv[1]);
  else
    return interpreter.repl();
}
