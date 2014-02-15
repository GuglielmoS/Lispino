#ifndef __NIL_H__
#define __NIL_H__

#include "Object.h"

namespace Lispino {

    class Nil : public Object {
    
        public:

            Object* eval(Environment& env) {
                return this;
            }

            int compare(Object* obj) {
                return obj->compareNil(this);
            }

            int compareNil(Nil* obj) {
                return 0;
            }

            int compareList(List* obj) {
                return -1;
            }

            int compareInt(IntNumber* obj) {
                return -1;
            }

            int compareFloat(FloatNumber* obj) {
                return -1;
            }

            int compareSymbol(Symbol* obj) {
                return -1;
            }

            int compareString(String* obj) {
                return -1;
            }
            
            int compareBoolean(Boolean* obj) {
                return -1;
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
