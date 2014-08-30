#include "Interpreter.h"

#include <iostream>
#include <cstring>

using namespace Lispino;

int main(int argc, char *argv[]) {
	Interpreter interpreter;
 
	// initialize the interpreter
	interpreter.init();

	// launch the REPL or execute a given file
	if (argc == 2) {
        if (!strcmp(argv[1], "-v")) {
            return interpreter.repl(true);
		} 
		else {
            return interpreter.execute(argv[1]);
		}
    }
    else {
        return interpreter.repl();
	}
}
