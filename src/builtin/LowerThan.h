#ifndef __BUILTIN_LOWER_THAN_H__
#define __BUILTIN_LOWER_THAN_H__

#include "BuiltinFunction.h"

namespace Lispino {

    class BuiltinLowerThan : public BuiltinFunction {

        public:

            Object* apply(std::vector<Object*>& args);

    };
};

#endif // __BUILTIN_LOWER_THAN_H__
