#ifndef __BUILTIN_EQUAL_H__
#define __BUILTIN_EQUAL_H__

#include "BuiltinFunction.h"
#include "../VM.h"

namespace Lispino {

    class BuiltinEqual : public BuiltinFunction {

        public:

            Object* apply(std::vector<Object*> args) {
                if (args.size() <= 1)
                    throw std::runtime_error("=: wrong number of arguments");

                for (unsigned int i = 0; i < args.size()-1; i++) {
                    if (!args[i]->equals(args[i+1]))
                        return VM::getAllocator().createBoolean(false);
                }

                return VM::getAllocator().createBoolean(true);
            }

    };
};

#endif // __BUILTIN_EQUAL_H__
