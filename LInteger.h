#ifndef __LINTEGER__

#define __LINTEGER__

#include <sstream>
#include <string>

#include "LObject.h"

#include "EvalException.h"

using namespace std;

class LInteger : public LObject {
    
    int value;
    
public:
    
    LInteger() : value(0) {}
    LInteger(int val) : value(val) {}

    LType getType() const {
        return ATOM_INTEGER;
    }

    string prettyString() const {
        stringstream buf;

        buf << value;

        return buf.str();
    }

    int getValue() {
        return value;
    }

    LObject* clone() const {
        return new LInteger(value);
    }

    LObject* eval(Environment& env) throw (EvalException) {
        return this;
    }

};

#endif // __LINTEGER__
