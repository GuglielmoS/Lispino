#ifndef __LINTEGER_H__
#define __LINTEGER_H__

// c++
#include <sstream>
#include <string>

// lisp objects
#include "LObject.h"

// exceptions
#include "EvalException.h"

class LInteger : public LObject {
    
    long int value;
    
public:
    
    LInteger() : value(0) {}
    LInteger(long int val) : value(val) {}

    LType getType() const {
        return ATOM_INTEGER;
    }

    std::string prettyString() const {
        std::stringstream buf;

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

#endif // __LINTEGER_H__
