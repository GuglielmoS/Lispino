#ifndef __LSTRING__

#define __LSTRING__

#include <string>

#include "LAtom.h"
#include "LAtomType.h"

using namespace std;

class LString : public LAtom {
    
    string *value;
    
public:
    
    LString() : value(new string("")) {}
    LString(const string& val) : value(new string(val)) {}

    LAtomType getAtomType() const {
        return STRING;
    }

    string prettyString() const {
        return "\"" + (*value) + "\"";
    }

    string getValue() {
        return *value;
    }

    ~LString() {
        delete value;
    }

};

#endif // __LSTRING__

