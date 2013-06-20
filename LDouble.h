#ifndef __LDOUBLE__

#define __LDOUBLE__

#include <sstream>
#include <string>

#include "LAtom.h"
#include "LAtomType.h"

using namespace std;

class LDouble : public LAtom {
    
    double value;
    
public:
    
    LDouble() : value(0.0) {}
    LDouble(double val) : value(val) {}

    LAtomType getAtomType() const {
        return DOUBLE;
    }

    string prettyString() const {
        stringstream buf;

        buf << value;

        return buf.str();
    }

    double getValue() {
        return value;
    }

};

#endif // __LDOUBLE__ 

