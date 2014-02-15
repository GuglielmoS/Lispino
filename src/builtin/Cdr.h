#ifndef __BUILTIN_CDR_H__
#define __BUILTIN_CDR_H__

#include "BuiltinFunction.h"

namespace Lispino {
    
    class BuiltinCdr : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*>& args, Environment& env);

    };
};

#endif // _BUILTIN_CDR_H__
