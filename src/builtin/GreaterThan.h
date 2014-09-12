#ifndef LISPINO_BUILTIN_GREATERTHAN_H_
#define LISPINO_BUILTIN_GREATERTHAN_H_

#include "BuiltinFunction.h"

namespace Lispino {

    class BuiltinGreaterThan : public BuiltinFunction {

        public:

            Object* apply(std::vector<Object*>& args, Environment& env);

    };
};

#endif // LISPINO_BUILTIN_GREATERTHAN_H_
