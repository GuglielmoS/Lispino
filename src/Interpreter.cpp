#include "Interpreter.h"
#include "Parser.h"
#include "VM.h"

#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

using namespace Lispino;

std::string Interpreter::humanTime(double time_spent) {
    std::stringstream buf;
    std::string unit;

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

int Interpreter::repl() {
    bool terminated = false;

    // Read - Eval - Print - Loop
    while (not terminated) {
        std::string inputExpr;

        // gets the expression
        std::cout << "> ";
        std::getline(std::cin, inputExpr);

        // evaluates the expression
        if (inputExpr == "quit")
            terminated = true;
        else if (inputExpr != "") {
            clock_t begin, end;
            double totalTime, parsingTime, evaluationTime, garbageCollectionTime;

            // if the execution time must be shown
            bool timeIt = false;
            if (inputExpr.find("time-it ") == 0) {
                inputExpr = inputExpr.substr(7, inputExpr.size()-7);
                timeIt = true;
            }

            // *** PARSING ***
            begin = clock();
            std::stringstream stream(inputExpr);
            Object *expr = Parser(&stream).parseExpr();
            end = clock();
            parsingTime = (double)(end - begin) / CLOCKS_PER_SEC;
            
            // *** EVALUATION ***
            begin = clock();
            std::cout << expr->eval()->toString() << std::endl;
            end = clock();
            evaluationTime = (double)(end - begin) / CLOCKS_PER_SEC;
            
            // *** GARBAGE COLLECTION ***
            begin = clock();
            VM::getMemory().cleanup();
            end = clock();
            garbageCollectionTime = (double)(end - begin) / CLOCKS_PER_SEC;

            // calculate the total execution time
            totalTime = parsingTime + evaluationTime + garbageCollectionTime;

            // shows the time
            if (timeIt) {
                std::cout << ";; Parsing Time:            " << humanTime(parsingTime) << std::endl;
                std::cout << ";; Evaluation Time:         " << humanTime(evaluationTime) << std::endl;
                std::cout << ";; Garbage Collection Time: " << humanTime(garbageCollectionTime) << std::endl;
                std::cout << ";; Total Time:              " << humanTime(totalTime) << std::endl;
            }
        }
    }

    return 0;
}

/*
            static int repl() {
                //std::stringstream stream("(+ 1 (+ 1 (+ 1 (+ 1)))) (1 2 3) nil (DEFINE x 1) x (quote (a b c)) (lambda (x) (+ x x))"); 
                //std::stringstream stream("(+ 1 1) (+ 1 (+ 1 2) 3)"); 
                std::stringstream stream("(car (quote (1 2 3))) 1 2 3 (cdr (quote (1 2 3)))");
                Parser parser(&stream);

                std::unique_ptr<std::vector<Object*>> expressions(parser.parse());
                for (unsigned int i = 0; i < expressions->size(); i++) {
                    std::cout << "IN:  " << expressions->at(i)->toString() << std::endl;
                    std::cout << "OUT: " << expressions->at(i)->eval(VM::getGlobalEnv())->toString() << std::endl;
                    std::cout << std::endl;
                }

                return 0;
            }
            */

