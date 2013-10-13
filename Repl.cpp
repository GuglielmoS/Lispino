#include "Repl.h"

// c++
#include <map>
#include <string>
#include <sstream>

// lisp objects
#include "LObject.h"

string Repl::humanTime(double time_spent) {
    stringstream buf;
    string unit;

    if (time_spent > 0.001)
        unit = "secs";
    else if (time_spent > 0.000001) {
        time_spent *= 1000.0;
        unit = "ms";
    }
    else if (time_spent > 0.000000001) {
        time_spent *= 1000000.0;
        unit = "us";
    }
    else {
        time_spent *= 1000000000.0;
        unit = "ns";
    }
    
    buf << time_spent << " " << unit;

    return buf.str();
}

int Repl::run() {
    Environment env;
    bool terminated = false;

    // Read - Eval - Print - Loop
    while (not terminated) {
        string inputExpr;

        // gets the expression
        cout << "> ";
        getline(cin, inputExpr);

        // evaluates the expression
        if (inputExpr == "quit")
            terminated = true;
        else if (inputExpr == "env-dump") {
            std::map<std::string, LObject*> *symbolsTable = env.getSymbolsTable();
            
            cout << "[ENV DUMP:" << endl;
            for(map<string, LObject*>::iterator it = symbolsTable->begin(); 
                it != symbolsTable->end(); ++it) 
              cout << "\t" << it->first << " = " << it->second << endl;
            cout << "]" << endl;
        }
        else if (inputExpr != "") {
            clock_t begin, end;
            double time_spent;

            // if the execution time must be shown
            bool timeIt = false;
            if (inputExpr.find("time-it ") == 0) {
                inputExpr = inputExpr.substr(7, inputExpr.size()-7);
                timeIt = true;
            }

            // for timing
            begin = clock();

            // parsing and evaluation
            try {
                cout << Parser::parse(inputExpr)->eval(env) << endl;
            } catch (LispinoException& e) {
                cout << "[RUNTIME-ERROR: "
                     << e.what()
                     << "]"
                     << endl;
            }
            
            // calcuates the elapsed time
            end = clock();
            time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

            // shows the time
            if (timeIt)
                cout << "[EXECUTION-TIME: "
                     << humanTime(time_spent)
                     << "]"
                     << endl;
        }
    }

    return 0;
}

