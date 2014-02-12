#ifndef __BUILTIN_MUL_H__
#define __BUILTIN_MUL_H__

#include "BuiltinFunction.h"
#include "../VM.h"
#include "../IntNumber.h"
#include "../FloatNumber.h"

namespace Lispino {
    
    class BuiltinMul : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*>& args) {
                if (args.size() <= 1)
                    throw std::runtime_error("*: wrong number of arguments!");
            
                // check if there are floats in the arguments
                bool isFloat = false;
                for (unsigned int i = 0; i < args.size() && !isFloat; i++) {
                    if (args[i]->isFloatNumber())
                        isFloat = true;
                    else if (!args[i]->isIntNumber())
                        throw std::runtime_error("*: invalid non-number argument!");
                }

                if (isFloat) {
                    float floatResult = 1.0f;

                    for (unsigned int i = 0; i < args.size(); i++) {
                        if (args[i]->isFloatNumber())
                            floatResult *= static_cast<FloatNumber*>(args[i])->getValue();
                        else
                            floatResult *= static_cast<IntNumber*>(args[i])->getValue();
                    }

                    return VM::getAllocator().createFloatNumber(floatResult);
                } else {
                    long int intResult = 1;
    
                    for (unsigned int i = 0; i < args.size(); i++) {
                        if (args[i]->isFloatNumber())
                            intResult *= static_cast<FloatNumber*>(args[i])->getValue();
                        else
                            intResult *= static_cast<IntNumber*>(args[i])->getValue();
                }

                    return VM::getAllocator().createIntNumber(intResult);
                }
            }

    };
};

#endif // _BUILTIN_MUL_H__
