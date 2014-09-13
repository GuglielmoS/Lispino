#include "Boolean.h"

namespace Lispino {

    Boolean::Boolean() : value(false) {
        /* DO NOTHING */
    }

    Boolean::Boolean(bool value) : value(value) {
        /* DO NOTHING */
    }

    void Boolean::setValue(bool value) {
        this->value = value;
    }

    bool Boolean::getValue() const {
        return value;
    }

    Object* Boolean::eval(Environment& env) {
        return this;
    }

    int Boolean::compare(Object* obj) {
        return obj->compareBoolean(this);
    }

    int Boolean::compareBoolean(Boolean* obj) {
        if (value == obj->value) return 0;
        else if (value == false) return 1;
        else                     return -1;
    }

    bool Boolean::isTrue() const {
        return value;
    }

    bool Boolean::isFalse() const {
        return !value;
    }

    bool Boolean::isBoolean() const {
        return true;
    }

    std::string Boolean::toString() const {
        return value ? "TRUE" : "FALSE";
    }
}
