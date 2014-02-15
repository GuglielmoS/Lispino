#ifndef __BUILTIN_CONS_H__
#define __BUILTIN_CONS_H__

#include "BuiltinFunction.h"

namespace Lispino {
    
    class BuiltinCons : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*>& args, Environment& env);

    };
};

#endif // _BUILTIN_CONS_H__
