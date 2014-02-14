#ifndef __BUILTIN_LOWER_THAN_H__
#define __BUILTIN_LOWER_THAN_H__

#include "BuiltinFunction.h"
#include "../VM.h"

namespace Lispino {

    class BuiltinLowerThan : public BuiltinFunction {

        public:

            Object* apply(std::vector<Object*>& args) {
                if (args.size() <= 1)
                    throw std::runtime_error("<: wrong number of arguments");

                if (args[0]->isFloatNumber()) {
                    float currentValue = static_cast<FloatNumber*>(args[0])->getValue();

                    for (unsigned int i = 1; i < args.size(); i++) {
                        if (args[i]->isFloatNumber()) {
                            if (!(currentValue < static_cast<FloatNumber*>(args[i])->getValue()))
                                return VM::getAllocator().createBoolean(false);
                        }
                        else if (args[i]->isIntNumber()) {
                            if (!(currentValue < static_cast<IntNumber*>(args[i])->getValue()))
                                return VM::getAllocator().createBoolean(false);
                        }
                        else
                            throw std::runtime_error("<: invalid non-number argument!");
                    }
                }
                else if (args[0]->isIntNumber()) {
                    long int currentValue = static_cast<IntNumber*>(args[0])->getValue();

                    for (unsigned int i = 1; i < args.size(); i++) {
                        if (args[i]->isFloatNumber()) {
                            if (!(currentValue < static_cast<FloatNumber*>(args[i])->getValue()))
                                return VM::getAllocator().createBoolean(false);
                        }
                        else if (args[i]->isIntNumber()) {
                            if (!(currentValue < static_cast<IntNumber*>(args[i])->getValue()))
                                return VM::getAllocator().createBoolean(false);                       
                        }
                        else
                            throw std::runtime_error("<: invalid non-number argument!");
                    }
                }
                else {
                    throw std::runtime_error("<: invalid non-number argument!");
                }

                return VM::getAllocator().createBoolean(true);
            }

    };
};

#endif // __BUILTIN_LOWER_THAN_H__
