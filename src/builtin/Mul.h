#ifndef __BUILTIN_MUL_H__
#define __BUILTIN_MUL_H__

#include "BuiltinFunction.h"

namespace Lispino {
    
    class BuiltinMul : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*>& args, Environment& env);

    };
};

#endif // _BUILTIN_MUL_H__
