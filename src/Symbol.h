#ifndef LISPINO_SYMBOL_H_
#define LISPINO_SYMBOL_H_

#include <string>

#include "Object.h"

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

#endif // LISPINO_SYMBOL_H_
