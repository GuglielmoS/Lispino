#ifndef __REPL_H__
#define __REPL_H__

// c++
#include <iostream>
#include <string>
#include <ctime>

// parsing
#include "Parser.h"

// evaluation
#include "Environment.h"

// exceptions
#include "LispinoException.h"

using namespace std;

class Repl {

public:

    static string humanTime(double time_spent);
    static int run();

};

#endif // __REPL_H__
