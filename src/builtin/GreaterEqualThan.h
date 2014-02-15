#ifndef __BUILTIN_GREATER_EQUAL_THAN_H__
#define __BUILTIN_GREATER_EQUAL_THAN_H__

#include "BuiltinFunction.h"

namespace Lispino {

    class BuiltinGreaterEqualThan : public BuiltinFunction {

        public:

            Object* apply(std::vector<Object*>& args, Environment& env);

    };
};

#endif // __BUILTIN_GREATER_EQUAL_THAN_H__
