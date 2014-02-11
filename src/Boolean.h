#ifndef __BOOLEAN_H__
#define __BOOLEAN_H__

#include "Object.h"

namespace Lispino {

    class Boolean : public Object {
        
        bool value;

        public:

            Boolean() : value(false) {}
            Boolean(bool value) : value(value) {}

            Object* eval(Environment& env) {
                return this;
            }

            void setValue(bool value) {
                this->value = value;
            }

            bool getValue() const {
                return value;
            }

            bool isTrue() const {
                return value;
            }

            bool isFalse() const {
                return !value;
            }

            bool isBoolean() const {
                return true;
            }

            std::string toString() const {
                return value ? "TRUE" : "FALSE";
            }

    };
};

#endif // __BOOLEAN_H__
