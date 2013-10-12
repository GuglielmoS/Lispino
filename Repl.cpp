#include "Repl.h"

#include <map>
#include <string>
#include "LObject.h"

int Repl::run() {
    cout.precision(15);

    Environment env;
    bool terminated = false;
    while (not terminated) {
        string inputExpr;

        cout << "> ";
        getline(cin, inputExpr);

        if (inputExpr == "(quit)" or inputExpr == "quit")
            terminated = true;
        else if (inputExpr == "env-dump") {
            std::map<std::string, LObject*> *symbolsTable = env.getSymbolsTable();
            
            cout << "[ENV DUMP]" << endl;
            for(map<string, LObject*>::iterator it = symbolsTable->begin(); 
                it != symbolsTable->end(); ++it) 
              cout << "\t" << it->first << " = " << it->second << endl;
        }
        else if (inputExpr != "") {
            time_t start, end;
            double dif = 0.0;

            bool timeIt = false;
            if (inputExpr.find("time-it ") == 0) {
                inputExpr = inputExpr.substr(7, inputExpr.size()-7);
                timeIt = true;
            }

            time(&start);

            try {
                LObject *result = Parser::parse(inputExpr)->eval(env);

                cout << result << endl;

                //if (not result->isNIL())
                //    delete result;

            } catch (LispinoException& e) {
                cout << "[RUNTIME-ERROR: "
                     << e.what()
                     << "]"
                     << endl;
            }
            
            time(&end);

            dif = difftime(end,start);
            float seconds = (float)(end - start) / CLOCKS_PER_SEC;

            if (timeIt)
                cout << "[EXECUTION-TIME: "
                     << fixed << seconds
                     << " seconds]"
                     << endl;
        }
    }

    return 0;
}

