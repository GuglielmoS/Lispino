#ifndef __BUILTIN_REMAINDER_H__
#define __BUILTIN_REMAINDER_H__

#include "BuiltinFunction.h"
#include "../VM.h"
#include "../IntNumber.h"
#include "../FloatNumber.h"

namespace Lispino {
    
    class BuiltinRemainder : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*>& args) {
                if (args.size() <= 1)
                    throw std::runtime_error("remainder: wrong number of arguments!");
        
                long int result = 0;

                if (args[0]->isFloatNumber())
                    result = static_cast<FloatNumber*>(args[0])->getValue();
                else if (args[0]->isIntNumber())
                    result = static_cast<IntNumber*>(args[0])->getValue();
                else
                        throw std::runtime_error("remainder: invalid non-number argument!");

                for (unsigned int i = 1; i < args.size(); i++) {
                    if (args[i]->isFloatNumber())
                        result %= (long int)(static_cast<FloatNumber*>(args[i])->getValue());
                    else if (args[i]->isIntNumber())
                        result %= static_cast<IntNumber*>(args[i])->getValue();
                    else
                        throw std::runtime_error("remainder: invalid non-number argument!");
                }

                return VM::getAllocator().createIntNumber(result);
            }

    };
};

#endif // _BUILTIN_REMAINDER_H__
