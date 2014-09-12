#ifndef LISPINO_BUILTIN_CONS_H_
#define LISPINO_BUILTIN_CONS_H_

#include "BuiltinFunction.h"

namespace Lispino {
    
    class BuiltinCons : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*>& args, Environment& env);

    };
};

#endif // LISPINO_BUILTIN_CONS_H_
