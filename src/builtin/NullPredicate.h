#ifndef __BUILTIN_NULL_PREDICATE_H__
#define __BUILTIN_NULL_PREDICATE_H__

#include "BuiltinFunction.h"

namespace Lispino {
    
    class BuiltinNullPredicate : public BuiltinFunction {
 
        public:

            Object* apply(std::vector<Object*>& args, Environment& env);

    };
};

#endif // _BUILTIN_NULL_PREDICATE_H__
