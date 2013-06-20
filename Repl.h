#ifndef __REPL__

#define __REPL__

#include <iostream>
#include <string>

#include "LObject.h"
#include "LNilObject.h"
#include "Environment.h"

using namespace std;

class Repl {

public:

    static int run() {
        Environment *env = new Environment();
        
        bool terminated = false;
        while (not terminated) {
            cout << "> ";

            string inputExpr;
            getline(cin, inputExpr);
        
            if (inputExpr == "quit")
                terminated = true;
            else
                cout << "\t" << env->eval(inputExpr) << endl;
        }

        delete env;

        return 0;
    }

};

#endif // __REPL__

