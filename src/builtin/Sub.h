#ifndef __BUILTIN_SUB_H__
#define __BUILTIN_SUB_H__

#include "BuiltinFunction.h"
#include "../VM.h"
#include "../IntNumber.h"
#include "../FloatNumber.h"

namespace Lispino {
    
    class BuiltinSub : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*>& args) {
                if (args.size() == 0)
                    throw std::runtime_error("-: wrong number of arguments!");

                // check if there are floats in the arguments
                bool isFloat = false;
                for (unsigned int i = 0; i < args.size() && !isFloat; i++) {
                    if (args[i]->isFloatNumber())
                        isFloat = true;
                    else if (!args[i]->isIntNumber())
                        throw std::runtime_error("-: invalid non-number argument!");
                }

                if (isFloat) {
                    float floatResult = 0.0f;
                    if (args[0]->isFloatNumber())
                        floatResult = static_cast<FloatNumber*>(args[0])->getValue();
                    else
                        floatResult = static_cast<IntNumber*>(args[0])->getValue();

                    for (unsigned int i = 1; i < args.size(); i++) {
                        if (args[i]->isFloatNumber())
                            floatResult -= static_cast<FloatNumber*>(args[i])->getValue();
                        else
                            floatResult -= static_cast<IntNumber*>(args[i])->getValue();
                    }

                    return VM::getAllocator().createFloatNumber(floatResult);
                } else {
                    long int intResult = static_cast<IntNumber*>(args[0])->getValue();
                    if (args[0]->isFloatNumber())
                        intResult = static_cast<FloatNumber*>(args[0])->getValue();
                    else
                        intResult = static_cast<IntNumber*>(args[0])->getValue();

                    for (unsigned int i = 1; i < args.size(); i++) {
                        if (args[i]->isFloatNumber())
                            intResult -= static_cast<FloatNumber*>(args[i])->getValue();
                        else
                            intResult -= static_cast<IntNumber*>(args[i])->getValue();
                    }

                    return VM::getAllocator().createIntNumber(intResult);
                }
            }

    };
};

#endif // _BUILTIN_SUB_H__
