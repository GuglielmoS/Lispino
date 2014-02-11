#ifndef __STRING_H__
#define __STRING_H__

#include "Object.h"

#include <sstream>
#include <string>

namespace Lispino {

    class String : public Object {

        std::string value;

        public:

            String() : value("") {}
            String(std::string value) : value(value) {}

            Object* eval(Environment& env) {
                return this;
            }

            bool equals(Object *obj) const {
                if (this == obj)
                    return true;
                else if (obj->isString())
                    return static_cast<String*>(obj)->value == value;
                else
                    return false;
            }

            void setValue(std::string value) {
                this->value = value;
            }

            std::string getValue() const {
                return value;
            }

            bool isAtom() const {
                return true;
            }

            bool isString() const {
                return true;
            }

            std::string toString() const {
                std::stringstream buf;
                buf << "\"" << value << "\"";
                return buf.str();
            }

    };
};

#endif // __STRING_H__
