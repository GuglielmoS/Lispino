#ifndef __REPL__

#define __REPL__

#include <iostream>
#include <string>
#include <ctime>

#include "Parser.h"
#include "Environment.h"
#include "LispinoException.h"

using namespace std;

class Repl {

public:

    static int run();

};

#endif // __REPL__

