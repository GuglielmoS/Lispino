#ifndef LISPINO_BUILTINS_LOWERTHAN_H_
#define LISPINO_BUILTINS_LOWERTHAN_H_

#include "BuiltinFunction.h"

namespace Lispino {
    namespace Builtins {
        class LowerThan : public BuiltinFunction {
            public:
                Object* apply(std::vector<Object*>& args, Environment& env);
        };
    }
}

#endif // LISPINO_BUILTINS_LOWERTHAN_H_
