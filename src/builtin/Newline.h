#ifndef LISPINO_BUILTIN_NEWLINE_H_
#define LISPINO_BUILTIN_NEWLINE_H_

#include <iostream>

#include "BuiltinFunction.h"
#include "../VM.h"

namespace Lispino {
    
    class BuiltinNewline : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*>& args, Environment& env) {
                if (args.size() != 0)
                    throw std::runtime_error("newline: wrong number of arguments!");

                // side effect
                std::cout << std::endl;
            
                return VM::getAllocator().createString("\n");
            }

    };
};

#endif // LISPINO_BUILTIN_NEWLINE_H_
