#include <iostream>

#include "Interpreter.h"

using namespace Lispino;

int main(int argc, char *argv[]) {
    return Interpreter().repl(); 
}
