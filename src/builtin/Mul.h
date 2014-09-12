#ifndef LISPINO_BUILTIN_MUL_H_
#define LISPINO_BUILTIN_MUL_H_

#include "BuiltinFunction.h"

namespace Lispino {
    
    class BuiltinMul : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*>& args, Environment& env);

    };
};

#endif // LISPINO_BUILTIN_MUL_H_
