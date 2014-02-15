#ifndef __INT_NUMBER_H__
#define __INT_NUMBER_H__

#include "Object.h"

#include <sstream>
#include <string>

namespace Lispino {

    class IntNumber : public Object {

        long int value;

        public:

            IntNumber() : value(0) {}
            IntNumber(long int value) : value(value) {}

            Object* eval(Environment& env);

            int compare(Object* obj);
            int compareInt(IntNumber* obj);
            int compareFloat(FloatNumber* obj);

            Object* add(Object* obj);
            Object* addInt(IntNumber* obj);
            Object* addFloat(FloatNumber* obj);
            Object* sub(Object* obj);
            Object* subInt(IntNumber* obj);
            Object* subFloat(FloatNumber* obj);
            Object* mul(Object* obj);
            Object* mulInt(IntNumber* obj);
            Object* mulFloat(FloatNumber* obj);
            Object* div(Object* obj);
            Object* divInt(IntNumber* obj);
            Object* divFloat(FloatNumber* obj);
            Object* remainder(Object* obj);
            Object* remainderInt(IntNumber* obj);

            void setValue(long int value);
            long int getValue() const;

            bool isAtom() const;
            bool isIntNumber() const;

            std::string toString() const;
    };
};

#endif // __INT_NUMBER_H__
