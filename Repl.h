#ifndef __REPL__

#define __REPL__

#include <iostream>
#include <string>

#include "Environment.h"
#include "LispinoException.h"

using namespace std;

class Repl {

public:

    static int run() {
        Environment env;
        
        bool terminated = false;
        while (not terminated) {
            string inputExpr;

            cout << "> ";
            getline(cin, inputExpr);

            if (inputExpr == "(quit)")
                terminated = true;
            else {
                cout << "\t";

                try {
                    cout << env.eval(inputExpr) << endl;
                } catch (LispinoException& e) {
                    cout << "[ERROR] " << e.what() << endl;
                }
            }
        }

        return 0;
    }

};

#endif // __REPL__

