#ifndef LISPINO_BUILTIN_CAR_H_
#define LISPINO_BUILTIN_CAR_H_

#include "BuiltinFunction.h"

namespace Lispino {
    
    class BuiltinCar : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*>& args, Environment& env);

    };
};

#endif // LISPINO_BUILTIN_CAR_H_
