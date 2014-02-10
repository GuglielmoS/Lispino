#ifndef __NIL_H__
#define __NIL_H__

#include "Object.h"

namespace Lispino {

    class Nil : public Object {
    
        public:

            Object* eval(Environment& env) {
                return this;
            }

            bool isNil() const {
                return true;
            }

            std::string toString() const {
                return "NIL";
            }

    };
};

#endif // __NIL_H__
