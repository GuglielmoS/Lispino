#ifndef __BUILTIN_NEWLINE_H__
#define __BUILTIN_NEWLINE_H__

#include "BuiltinFunction.h"
#include "../VM.h"

namespace Lispino {
    
    class BuiltinNewline : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*>& args, Environment& env) {
                if (args.size() != 0)
                    throw std::runtime_error("newline: wrong number of arguments!");
            
                return VM::getAllocator().createString("\n");
            }

    };
};

#endif // _BUILTIN_ADD_H__
