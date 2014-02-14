#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include "Object.h"

#include <string>

namespace Lispino {

    class Symbol : public Object {

        std::string value;

        public:

            Symbol() : value("") {}
            Symbol(std::string value) : value(value) {}

            Object* eval(Environment& env);

            bool equals(Object *obj) const {
                if (this == obj)
                    return true;
                else if (obj->isSymbol())
                    return static_cast<Symbol*>(obj)->value == value;
                else
                    return false;
            }

            std::string& getValue() {
                return value;
            }

            inline void setValue(std::string value) {
                this->value = value;
            }

            bool isAtom() const {
                return true;
            }

            bool isSymbol() const {
                return true;
            }

            std::string toString() const {
                return value;
            }

    };
};

#endif // __SYMBOL_H__
