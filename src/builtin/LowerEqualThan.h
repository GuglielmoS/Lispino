#ifndef LISPINO_BUILTIN_LOWEREQUALTHAN_H_
#define LISPINO_BUILTIN_LOWEREQUALTHAN_H_

#include "BuiltinFunction.h"

namespace Lispino {

    class BuiltinLowerEqualThan : public BuiltinFunction {

        public:

            Object* apply(std::vector<Object*>& args, Environment& env);

    };
};

#endif // LISPINO_BUILTIN_LOWEREQUALTHAN_H_
