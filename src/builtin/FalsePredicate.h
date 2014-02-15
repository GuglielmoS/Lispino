#ifndef __BUILTIN_FALSE_PREDICATE_H__
#define __BUILTIN_FALSE_PREDICATE_H__

#include "BuiltinFunction.h"

namespace Lispino {
    
    class BuiltinFalsePredicate : public BuiltinFunction {
 
        public:

            Object* apply(std::vector<Object*>& args, Environment& env);

    };
};

#endif // _BUILTIN_FALSE_PREDICATE_H__
