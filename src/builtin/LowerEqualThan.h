#ifndef __BUILTIN_LOWER_EQUAL_THAN_H__
#define __BUILTIN_LOWER_EQUAL_THAN_H__

#include "BuiltinFunction.h"

namespace Lispino {

    class BuiltinLowerEqualThan : public BuiltinFunction {

        public:

            Object* apply(std::vector<Object*>& args, Environment& env);

    };
};

#endif // __BUILTIN_LOWER_EQUAL_THAN_H__
