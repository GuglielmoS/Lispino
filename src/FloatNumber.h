#ifndef __FLOAT_NUMBER_H__
#define __FLOAT_NUMBER_H__

#include "Object.h"

#include <sstream>
#include <string>

namespace Lispino {

    class FloatNumber : public Object {

        float value;

        public:

            FloatNumber() : value(0.0f) {}
            FloatNumber(float value) : value(value) {}

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
            Object* remainderFloat(FloatNumber* obj);

            void setValue(float value);
            float getValue() const;

            bool isAtom() const;
            bool isFloatNumber() const;

            std::string toString() const;
    };
};

#endif // __FLOAT_NUMBER_H__
