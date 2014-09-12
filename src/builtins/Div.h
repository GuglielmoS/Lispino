#ifndef LISPINO_BUILTINS_DIV_H_
#define LISPINO_BUILTINS_DIV_H_

#include "BuiltinFunction.h"

namespace Lispino {

    namespace Builtins {

        class Div : public BuiltinFunction {
            public:

                Object* apply(std::vector<Object*>& args, Environment& env);
        };
    }
}

#endif // LISPINO_BUILTINS_DIV_H_
