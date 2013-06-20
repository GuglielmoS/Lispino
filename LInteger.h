#ifndef __LINTEGER__

#define __LINTEGER__

#include <sstream>
#include <string>

#include "LAtom.h"
#include "LAtomType.h"

using namespace std;

class LInteger : public LAtom {
    
    int value;
    
public:
    
    LInteger() : value(0) {}
    LInteger(int val) : value(val) {}

    LAtomType getAtomType() const {
        return INTEGER;
    }

    string prettyString() const {
        stringstream buf;

        buf << value;

        return buf.str();
    }

    int getValue() {
        return value;
    }

};

#endif // __LINTEGER__
