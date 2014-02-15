#ifndef __BUILTIN_REMAINDER_H__
#define __BUILTIN_REMAINDER_H__

#include "BuiltinFunction.h"

namespace Lispino {
    
    class BuiltinRemainder : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*>& args, Environment& env);

    };
};

#endif // _BUILTIN_REMAINDER_H__
