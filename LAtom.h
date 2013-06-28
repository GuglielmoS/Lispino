#ifndef __LATOM__ 

#define __LATOM__

#include <string>

#include "LObject.h"
#include "LType.h"
#include "LAtomType.h"

class LAtom : public LObject {

public:

    bool isInteger() const;
    bool isDouble() const;
    bool isSymbol() const;
    bool isString() const;

    LType getType() const;
    virtual LAtomType getAtomType() const = 0;

};

#endif // __LATOM__
