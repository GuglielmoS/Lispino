#ifndef __LDOUBLE__

#define __LDOUBLE__

#include <sstream>
#include <string>

#include "LObject.h"
#include "EvalException.h"

using namespace std;

class LDouble : public LObject {
    
    double value;
    
public:
    
    LDouble() : value(0.0) {}
    LDouble(double val) : value(val) {}

    LType getType() const {
        return ATOM_DOUBLE;
    }

    string prettyString() const {
        stringstream buf;

        buf << value;

        return buf.str();
    }

    double getValue() {
        return value;
    }

    LObject* clone() const {
        return new LDouble(value);
    }

    LObject* eval(Environment& env) throw (EvalException) {
        return const_cast<LDouble*>(this);
    }

};

#endif // __LDOUBLE__ 

