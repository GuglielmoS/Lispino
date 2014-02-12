#ifndef __BUILTIN_FUNCTION_H__
#define __BUILTIN_FUNCTION_H__

#include "../Object.h"

#include <vector>

namespace Lispino {

    class BuiltinFunction : public Object {
    
        public:

            Object* eval(Environment& env) {
                return this;
            }

            virtual Object* apply(std::vector<Object*>& args) = 0;

            bool equals(Object* obj) const {
                return this == obj;
            }

            bool isBuiltinFunction() const {
                return true;
            }

            std::string toString() const {
                return "BUILTIN-FUNCTION";
            }

    };
};

#endif // __BUILTIN_FUNCTION_H__
