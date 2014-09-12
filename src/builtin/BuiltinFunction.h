#ifndef LISPINO_BUILTIN_FUNCTION_H_
#define LISPINO_BUILTIN_FUNCTION_H_

#include <vector>

#include "../Object.h"

namespace Lispino {

    class BuiltinFunction : public Object {
    
        public:

            Object* eval(Environment& env) {
                return this;
            }

            virtual Object* apply(std::vector<Object*>& args, Environment& env) = 0;

            bool isBuiltinFunction() const {
                return true;
            }

            std::string toString() const {
                return "BUILTIN-FUNCTION";
            }

    };
};

#endif // LISPINO_BUILTIN_FUNCTION_H_
