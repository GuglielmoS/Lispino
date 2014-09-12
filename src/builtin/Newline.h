#ifndef LISPINO_BUILTIN_NEWLINE_H_
#define LISPINO_BUILTIN_NEWLINE_H_

#include "BuiltinFunction.h"

namespace Lispino {
    
    class BuiltinNewline : public BuiltinFunction {
        public:
            Object* apply(std::vector<Object*>& args, Environment& env);
    };
};

#endif // LISPINO_BUILTIN_NEWLINE_H_
