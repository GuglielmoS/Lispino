#ifndef __BUILTIN_DIV_H__
#define __BUILTIN_DIV_H__

#include "BuiltinFunction.h"
#include "../VM.h"
#include "../IntNumber.h"
#include "../FloatNumber.h"

namespace Lispino {
    
    class BuiltinDiv : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*>& args) {
                if (args.size() <= 1)
                    throw std::runtime_error("/: wrong number of arguments!");
            
                float floatResult = 0.0f;

                if (args[0]->isFloatNumber())
                    floatResult = static_cast<FloatNumber*>(args[0])->getValue();
                else if (args[0]->isIntNumber())
                    floatResult = static_cast<IntNumber*>(args[0])->getValue();
                else
                    throw std::runtime_error("/: invalid non-number argument!");

                for (unsigned int i = 1; i < args.size(); i++) {
                    if (args[i]->isFloatNumber())
                        floatResult /= static_cast<FloatNumber*>(args[i])->getValue();
                    else if (args[i]->isIntNumber())
                        floatResult /= static_cast<IntNumber*>(args[i])->getValue();
                    else
                        throw std::runtime_error("/: invalid non-number argument!");
                }

                return VM::getAllocator().createFloatNumber(floatResult);
            }

    };
};

#endif // _BUILTIN_DIV_H__
