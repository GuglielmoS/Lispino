#ifndef __LSTRING__

#define __LSTRING__

#include <string>

#include "LObject.h"
#include "EvalException.h"

using namespace std;

class LString : public LObject {
    
    string *value;
    
public:
    
    LString() : value(new string("")) {}
    LString(const string& val) : value(new string(val)) {}

    LType getType() const {
        return ATOM_STRING;
    }

    string prettyString() const {
        return "\"" + (*value) + "\"";
    }

    string getValue() {
        return *value;
    }

    LObject* clone() const {
        return new LString(*value);
    }

    LObject* eval(Environment& env) throw (EvalException) {
        return this;
    }

    ~LString() {
        delete value;
    }

};

#endif // __LSTRING__

