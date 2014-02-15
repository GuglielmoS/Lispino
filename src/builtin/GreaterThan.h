#ifndef __BUILTIN_GREATER_THAN_H__
#define __BUILTIN_GREATER_THAN_H__

#include "BuiltinFunction.h"

namespace Lispino {

    class BuiltinGreaterThan : public BuiltinFunction {

        public:

            Object* apply(std::vector<Object*>& args);

    };
};

#endif // __BUILTIN_GREATER_THAN_H__
