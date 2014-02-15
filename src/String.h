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

#endif // __STRING_H__
