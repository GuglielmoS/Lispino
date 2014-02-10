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
