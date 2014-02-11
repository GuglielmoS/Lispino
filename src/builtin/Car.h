#ifndef __BUILTIN_CAR_H__
#define __BUILTIN_CAR_H__

#include "BuiltinFunction.h"
#include "../VM.h"

namespace Lispino {
    
    class BuiltinCar : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*> args) {
                if (args.size() != 1)
                    return VM::getAllocator().createNil();

                if (!args[0]->isList())
                    return VM::getAllocator().createNil();

                return static_cast<List*>(args[0])->getFirst();
            }

    };
};

#endif // _BUILTIN_CAR_H__
