#ifndef LISPINO_NIL_H_
#define LISPINO_NIL_H_

#include "Object.h"

namespace Lispino {

    class Nil : public Object {
    
        public:

            Object* eval(Environment& env);

            int compare(Object* obj);
            int compareNil(Nil* obj);
            int compareList(List* obj);
            int compareInt(IntNumber* obj);
            int compareFloat(FloatNumber* obj);
            int compareSymbol(Symbol* obj);
            int compareString(String* obj);
            int compareBoolean(Boolean* obj);
            int compareSequence(Sequence* obj);

            bool isNil() const;
            
            std::string toString() const;
    };
};

#endif // LISPINO_NIL_H_
