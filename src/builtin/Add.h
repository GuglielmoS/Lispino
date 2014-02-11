#ifndef __BUILTIN_ADD_H__
#define __BUILTIN_ADD_H__

#include "BuiltinFunction.h"
#include "../VM.h"
#include "../IntNumber.h"
#include "../FloatNumber.h"

namespace Lispino {
    
    class BuiltinAdd : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*> args) {
                if (args.size() <= 1)
                    throw std::runtime_error("+: wrong number of arguments!");

                bool isFloat = false;
                float floatResult = 0.0f;
                long int intResult = 0;

                for (unsigned int i = 0; i < args.size(); i++) {
                    if (args[i]->isFloatNumber()) {
                        isFloat = true;
                        floatResult += static_cast<FloatNumber*>(args[i])->getValue();
                    } else if (args[i]->isIntNumber()) {
                        intResult += static_cast<IntNumber*>(args[i])->getValue();
                    }
                }
                
                if (isFloat)
                    return VM::getAllocator().createFloatNumber(floatResult + intResult);
                else
                    return VM::getAllocator().createIntNumber(floatResult + intResult);
            }

    };
};

#endif // _BUILTIN_ADD_H__
