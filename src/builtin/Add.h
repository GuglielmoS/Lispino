#ifndef LISPINO_BUILTIN_ADD_H_
#define LISPINO_BUILTIN_ADD_H_

#include "BuiltinFunction.h"

namespace Lispino {
    
    class BuiltinAdd : public BuiltinFunction {
 
        public:

            Object* apply(std::vector<Object*>& args, Environment& env);

    };
};

#endif // LISPINO_BUILTIN_ADD_H_
