#ifndef __BUILTIN_DIV_H__
#define __BUILTIN_DIV_H__

#include "BuiltinFunction.h"

namespace Lispino {
    
    class BuiltinDiv : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*>& args);

    };
};

#endif // _BUILTIN_DIV_H__
