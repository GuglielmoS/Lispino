#ifndef __LSYMBOL__

#define __LSYMBOL__

#include <string>

#include "LAtom.h"
#include "LAtomType.h"

using namespace std;

class LSymbol : public LAtom {
    
    string *value;

public:
    
    LSymbol(const string& val) : value(new string(val)) {}

    LAtomType getAtomType() const {
        return SYMBOL;
    }

    string prettyString() const {
        return *value;
    }

    string getValue() {
        return *value;
    }

    ~LSymbol() {
        delete value;
    }

};

#endif // __LSYMBOL__

