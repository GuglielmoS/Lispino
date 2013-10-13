#ifndef __LSTRING_H__
#define __LSTRING_H__

// c++
#include <string>

// lisp objects
#include "LObject.h"

// exceptions
#include "EvalException.h"

class LString : public LObject {
    
    std::string *value;
    
public:
    
    LString() : value(new std::string("")) {}
    LString(const std::string& val) : value(new std::string(val)) {}

    LType getType() const {
        return ATOM_STRING;
    }

    std::string prettyString() const {
        return "\"" + (*value) + "\"";
    }

    std::string getValue() {
        return *value;
    }

    LObject* eval(Environment& env) throw (EvalException) {
        return this;
    }

    ~LString() {
        delete value;
    }

};

#endif // __LSTRING_H__

