#ifndef LISPINO_BUILTIN_DISPLAY_H_
#define LISPINO_BUILTIN_DISPLAY_H_

#include <vector>

#include "BuiltinFunction.h"
#include "../VM.h"

namespace Lispino {
    
    class BuiltinDisplay : public BuiltinFunction {
        public:
            Object* apply(std::vector<Object*>& args, Environment& env);
    };
};

#endif // LISPINO_BUILTIN_ADD_H_
