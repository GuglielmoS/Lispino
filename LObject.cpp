#include "LObject.h"

bool LObject::isAtom() const {
    return getType() == ATOM;
}

bool LObject::isCons() const {
    return getType() == CONS;
}

bool LObject::isLambda() const {
    return getType() == LAMBDA;
}

bool LObject::isNIL() const {
    return getType() == NIL;
}

std::ostream& operator<<(std::ostream& out, LObject* obj) {
    out << obj->prettyString();
    return out;
}

