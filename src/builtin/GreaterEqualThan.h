#ifndef LISPINO_BUILTIN_GREATEREQUALTHAN_H_
#define LISPINO_BUILTIN_GREATEREQUALTHAN_H_

#include "BuiltinFunction.h"

namespace Lispino {

    class BuiltinGreaterEqualThan : public BuiltinFunction {

        public:

            Object* apply(std::vector<Object*>& args, Environment& env);

    };
};

#endif // LISPINO_BUILTIN_GREATEREQUALTHAN_H_
