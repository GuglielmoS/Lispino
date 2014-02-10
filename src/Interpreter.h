#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include "VM.h"
#include "Parser.h"

#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

namespace Lispino {

    class Interpreter {
    
        public:

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

    };
};

#endif // __INTERPRETER_H__
