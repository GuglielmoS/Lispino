#ifndef LISPINO_BUILTIN_LOWERTHAN_H_
#define LISPINO_BUILTIN_LOWERTHAN_H_

#include "BuiltinFunction.h"

namespace Lispino {

    class BuiltinLowerThan : public BuiltinFunction {

        public:

            Object* apply(std::vector<Object*>& args, Environment& env);

    };
};

#endif // LISPINO_BUILTIN_LOWERTHAN_H_
