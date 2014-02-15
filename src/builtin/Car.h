#ifndef __BUILTIN_CAR_H__
#define __BUILTIN_CAR_H__

#include "BuiltinFunction.h"

namespace Lispino {
    
    class BuiltinCar : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*>& args, Environment& env);

    };
};

#endif // _BUILTIN_CAR_H__
