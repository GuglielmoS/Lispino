#ifndef LISPINO_STRING_H_
#define LISPINO_STRING_H_

#include <sstream>
#include <string>

#include "Object.h"

namespace Lispino {

    class String : public Object {

        std::string value;

        public:

            String() : value("") {}
            String(std::string value) : value(value) {}

            Object* eval(Environment& env);

            int compare(Object* obj);
            int compareString(String* obj);

            void setValue(std::string value);
            std::string getValue() const;

            bool isAtom() const;
            bool isString() const;

            std::string toString() const;
    };
};

#endif // LISPINO_STRING_H_
