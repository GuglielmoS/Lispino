#ifndef __BUILTIN_CDR_H__
#define __BUILTIN_CDR_H__

#include "BuiltinFunction.h"
#include "../VM.h"

namespace Lispino {
    
    class BuiltinCdr : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*> args) {
                if (args.size() != 1)
                    return VM::getAllocator().createNil();

                if (!args[0]->isList())
                    return VM::getAllocator().createNil();

                return static_cast<List*>(args[0])->getRest();
            }

    };
};

#endif // _BUILTIN_CDR_H__
