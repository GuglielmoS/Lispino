#include "Interpreter.h"
#include "Parser.h"
#include "VM.h"

#include <iostream>
#include <fstream>
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

int Interpreter::repl(bool verbose) {
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
            std::stringstream stream(inputExpr);

            // *** PARSING ***
            begin = clock();
            Object *expr = Parser(stream).parse();
            end = clock();
            parsingTime = (double)(end - begin) / CLOCKS_PER_SEC;
            
            // *** EVALUATION ***
            begin = clock();
            std::cout << expr->eval()->toString() << std::endl;
            end = clock();
            evaluationTime = (double)(end - begin) / CLOCKS_PER_SEC;
            
            // *** GARBAGE COLLECTION ***
            size_t totalObjects = VM::getMemory().getAllocatedObjects();
            begin = clock();
            size_t removedObjects = VM::getMemory().cleanup();
            end = clock();
            garbageCollectionTime = (double)(end - begin) / CLOCKS_PER_SEC;

            // calculate the total execution time
            totalTime = parsingTime + evaluationTime + garbageCollectionTime;

            // shows the time
            if (verbose) {
                std::cout << ";; Timing report" << std::endl;
                std::cout << "     + Parsing Time:            " << parsingTime << std::endl;
                std::cout << "     + Evaluation Time:         " << evaluationTime << std::endl;
                std::cout << "     + Garbage Collection Time: " << garbageCollectionTime << std::endl;
                std::cout << "     Total Time:                " << totalTime << std::endl;
                std::cout << ";; Memory report" << std::endl;
                std::cout << "     Garbage collected objects " <<  removedObjects << "/" << totalObjects << std::endl;
            }
        }
    }

    return 0;
}

int Interpreter::execute(std::string filename) {
    std::ifstream inputStream(filename);
    
    if (inputStream.is_open()) {
        Parser parser(inputStream);

        Object *currentExpr = nullptr;
        while ((currentExpr = parser.parseExpr()) != nullptr) {
            currentExpr->eval()->toString();
            VM::getMemory().cleanup();
        }

        inputStream.close();

        return 0;
    }
    else {
        std::cerr << "File not found: " << filename << std::endl;
        return 1;
    }
}
