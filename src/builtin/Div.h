#ifndef LISPINO_BUILTIN_DIV_H_
#define LISPINO_BUILTIN_DIV_H_

#include "BuiltinFunction.h"

namespace Lispino {
    
    class BuiltinDiv : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*>& args, Environment& env);

    };
};

#endif // LISPINO_BUILTIN_DIV_H_
