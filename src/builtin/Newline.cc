#include "Newline.h"

#include <iostream>

#include "../VM.h"

namespace Lispino {
    Object* BuiltinNewline::apply(std::vector<Object*>& args, Environment& env) {
        if (args.size() != 0)
            throw std::runtime_error("newline: wrong number of arguments!");

        // side effect
        std::cout << std::endl;
    
        return VM::getAllocator().createString("\n");
    }
}
