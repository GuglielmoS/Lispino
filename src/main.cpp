#include "Interpreter.h"

#include <iostream>
#include <cstring>

using namespace Lispino;

int main(int argc, char *argv[]) {
    if (argc == 2) {
        if (!strcmp(argv[1], "-v"))
            return Interpreter::repl(true);
        else
            return Interpreter::execute(argv[1]);
    }
    else
        return Interpreter::repl();
}
