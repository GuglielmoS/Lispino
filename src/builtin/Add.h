#ifndef __BUILTIN_ADD_H__
#define __BUILTIN_ADD_H__

#include "BuiltinFunction.h"

namespace Lispino {
    
    class BuiltinAdd : public BuiltinFunction {
 
        public:

            Object* apply(std::vector<Object*>& args, Environment& env);

    };
};

#endif // _BUILTIN_ADD_H__
