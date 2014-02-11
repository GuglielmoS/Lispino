#ifndef __BUILTIN_FUNCTION_H__
#define __BUILTIN_FUNCTION_H__

#include "../Object.h"

#include <vector>

namespace Lispino {

    class BuiltinFunction {
    
        public:
    
            virtual Object* apply(std::vector<Object*> args) = 0;

    };
};

#endif // __BUILTIN_FUNCTION_H__
