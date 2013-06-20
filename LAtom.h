#ifndef __LATOM__ 

#define __LATOM__

#include <string>

#include "LObject.h"
#include "LType.h"
#include "LAtomType.h"

using namespace std;

class LAtom : public LObject {

public:

    LType getType() const {
        return ATOM;
    }

    bool isInteger() const {
        return getAtomType() == INTEGER;
    }

    bool isDouble() const {
        return getAtomType() == DOUBLE;
    }

    bool isSymbol() const {
        return getAtomType() == SYMBOL;
    }

    bool isString() const {
        return getAtomType() == STRING;
    }

    virtual LAtomType getAtomType() const = 0;
};

#endif // __LATOM__
