#include "LAtom.h"

LType LAtom::getType() const {
    return ATOM;
}

bool LAtom::isInteger() const {
    return getAtomType() == INTEGER;
}

bool LAtom::isDouble() const {
    return getAtomType() == DOUBLE;
}

bool LAtom::isSymbol() const {
    return getAtomType() == SYMBOL;
}

bool LAtom::isString() const {
    return getAtomType() == STRING;
}

