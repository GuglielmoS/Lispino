#ifndef __BUILTIN_CONS_H__
#define __BUILTIN_CONS_H__

#include "BuiltinFunction.h"
#include "../VM.h"

namespace Lispino {
    
    class BuiltinCons : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*> args) {
                if (args.size() != 2)
                    throw std::runtime_error("CONS: wrong number of arguments!");

                return VM::getAllocator().createList(args[0], args[1]);
            }

    };
};

#endif // _BUILTIN_CONS_H__
