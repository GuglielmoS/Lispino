#ifndef __NIL_H__
#define __NIL_H__

#include "Object.h"

namespace Lispino {

    class Nil : public Object {
    
        public:

            Object* eval(Environment& env) {
                return this;
            }

            bool equals(Object *obj) const {
                if (this == obj)
                    return true;
                else
                    return obj->isNil();
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
