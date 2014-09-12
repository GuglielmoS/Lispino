#ifndef LISPINO_BUILTIN_EQUAL_H_
#define LISPINO_BUILTIN_EQUAL_H_

#include "BuiltinFunction.h"

namespace Lispino {

    class BuiltinEqual : public BuiltinFunction {

        public:

            Object* apply(std::vector<Object*>& args, Environment& env);

    };
};

#endif // LISPINO_BUILTIN_EQUAL_H_
