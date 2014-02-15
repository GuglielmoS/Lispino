#ifndef __BUILTIN_EQUAL_H__
#define __BUILTIN_EQUAL_H__

#include "BuiltinFunction.h"

namespace Lispino {

    class BuiltinEqual : public BuiltinFunction {

        public:

            Object* apply(std::vector<Object*>& args);

    };
};

#endif // __BUILTIN_EQUAL_H__
