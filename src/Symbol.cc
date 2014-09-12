#include "Symbol.h"

#include "Environment.h"

namespace Lispino {
    Object* Symbol::eval(Environment& env) {
        return env.get(this);
    }

    int Symbol::compare(Object* obj) {
        if (obj == this) return 0;
        else             return obj->compareSymbol(this);
    }

    int Symbol::compareSymbol(Symbol* obj) {
        return obj->getValue().compare(value);
    }

    std::string& Symbol::getValue() {
        return value;
    }

    void Symbol::setValue(std::string value) {
        this->value = value;
    }

    bool Symbol::isAtom() const {
        return true;
    }

    bool Symbol::isSymbol() const {
        return true;
    }

    std::string Symbol::toString() const {
        return value;
    }
}
