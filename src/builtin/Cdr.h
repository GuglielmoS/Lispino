#ifndef LISPINO_BUILTIN_CDR_H_
#define LISPINO_BUILTIN_CDR_H_

#include "BuiltinFunction.h"

namespace Lispino {
    
    class BuiltinCdr : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*>& args, Environment& env);

    };
};

#endif // LISPINO_BUILTIN_CDR_H_
