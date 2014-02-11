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

            Object* eval(Environment& env) {
                return this;
            }

            bool equals(Object *obj) const {
                if (this == obj)
                    return true;
                else if (obj->isIntNumber())
                    return static_cast<IntNumber*>(obj)->value == value;
                else
                    return false;
            }

            void setValue(long int value) {
                this->value = value;
            }

            long int getValue() const {
                return value;
            }

            bool isAtom() const {
                return true;
            }

            bool isIntNumber() const {
                return true;
            }

            std::string toString() const {
                std::stringstream buf;
                buf << value;
                return buf.str();
            }

    };
};

#endif // __INT_NUMBER_H__
