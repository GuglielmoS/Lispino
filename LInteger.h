#ifndef __LINTEGER__

#define __LINTEGER__

#include <sstream>
#include <string>

#include "LObject.h"

#include "EvalException.h"

using namespace std;

class LInteger : public LObject {
    
    long int value;
    
public:
    
    LInteger() : value(0) {}
    LInteger(long int val) : value(val) {}

    LType getType() const {
        return ATOM_INTEGER;
    }

    string prettyString() const {
        stringstream buf;

        buf << value;

        return buf.str();
    }

    long int getValue() {
        return value;
    }

    bool equals(const LObject* otherObj) const {
        if (getType() != otherObj->getType())
            return false;

        const LInteger *otherInteger = dynamic_cast<const LInteger*>(otherObj);

        if (value != otherInteger->value)
            return false;

        return true;
    }

    LObject* eval(Environment& env) throw (EvalException) {
        return this;
    }

};

#endif // __LINTEGER__
