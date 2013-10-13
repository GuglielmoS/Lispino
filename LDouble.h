#ifndef __LDOUBLE_H__
#define __LDOUBLE_H__

// c++
#include <sstream>
#include <string>

// lisp objects
#include "LObject.h"

// exceptions
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

    bool equals(const LObject* otherObj) const {
        if (getType() != otherObj->getType())
            return false;

        const LDouble *otherDouble = dynamic_cast<const LDouble*>(otherObj);

        if (value != otherDouble->value)
            return false;

        return true;
    }

    LObject* eval(Environment& env) throw (EvalException) {
        return const_cast<LDouble*>(this);
    }

};

#endif // __LDOUBLE_H__ 

