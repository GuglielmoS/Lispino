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

            int compare(Object* obj);
            int compareSymbol(Symbol* obj);

            void setValue(std::string value);
            std::string& getValue();
            
            bool isAtom() const;
            bool isSymbol() const;

            std::string toString() const;
    };
};

#endif // __SYMBOL_H__
