#ifndef __BUILTIN_SUB_H__
#define __BUILTIN_SUB_H__

#include "BuiltinFunction.h"
#include "../VM.h"
#include "../IntNumber.h"
#include "../FloatNumber.h"

namespace Lispino {
    
    class BuiltinSub : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*>& args, Environment& env);

    };
};

#endif // _BUILTIN_SUB_H__
