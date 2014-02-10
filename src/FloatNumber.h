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

            Object* eval(Environment& env) {
                return this;
            }

            void setValue(float value) {
                this->value = value;
            }

            float getValue() const {
                return value;
            }

            bool isAtom() const {
                return true;
            }
            
            bool isFloatNumber() const {
                return true;
            }

            std::string toString() const {
                std::stringstream buf;
                buf << value;
                return buf.str();
            }

    };
};

#endif // __FLOAT_NUMBER_H__
