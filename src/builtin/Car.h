#ifndef __BUILTIN_CAR_H__
#define __BUILTIN_CAR_H__

#include "BuiltinFunction.h"
#include "../VM.h"

namespace Lispino {
    
    class BuiltinCar : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*>& args, Environment& env) {
                if (args.size() != 1)
                    return VM::getAllocator().createNil();

                Object *value = args[0]->eval(env);
                if (!value->isList())
                    return VM::getAllocator().createNil();
                else
                    return static_cast<List*>(value)->getFirst();
            }

    };
};

#endif // _BUILTIN_CAR_H__
