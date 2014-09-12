#ifndef LISPINO_BUILTIN_FUNCTION_H_
#define LISPINO_BUILTIN_FUNCTION_H_

#include <vector>

#include "../Object.h"

namespace Lispino {

    class BuiltinFunction : public Object {
    
        public:

            virtual Object* apply(std::vector<Object*>& args, Environment& env) = 0;

            Object* eval(Environment& env);

            bool isBuiltinFunction() const;

            std::string toString() const;
    };
};

#endif // LISPINO_BUILTIN_FUNCTION_H_
