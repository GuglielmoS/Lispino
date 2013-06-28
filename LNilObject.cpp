#include "LNilObject.h"

LType LNilObject::getType() const {
    return NIL;
}

std::string LNilObject::prettyString() const {
    return "NIL";
}

