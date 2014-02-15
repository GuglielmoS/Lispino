#ifndef __BUILTIN_TRUE_PREDICATE_H__
#define __BUILTIN_TRUE_PREDICATE_H__

#include "BuiltinFunction.h"

namespace Lispino {
    
    class BuiltinTruePredicate : public BuiltinFunction {
 
        public:

            Object* apply(std::vector<Object*>& args, Environment& env);

    };
};

#endif // _BUILTIN_TRUE_PREDICATE_H__
