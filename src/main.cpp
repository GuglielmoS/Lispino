#include <iostream>

#include "Interpreter.h"

using namespace Lispino;

int main(int argc, char *argv[]) {
    if (argc == 1)
        return Interpreter::repl(); 
    else
        return Interpreter::execute(argv[1]);
}
