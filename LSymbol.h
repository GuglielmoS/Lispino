#ifndef __LSYMBOL_H__
#define __LSYMBOL_H__

// c++
#include <string>

// lisp objects
#include "LObject.h"

// execptions
#include "EvalException.h"

class LSymbol : public LObject {

    std::string *value;

public:
    
    LSymbol(const std::string& val) : value(new std::string(val)) {}

    LType getType() const {
        return ATOM_SYMBOL;
    }

    std::string prettyString() const {
        return *value;
    }

    std::string getValue() {
        return *value;
    }

    LObject* clone() const {
        return new LSymbol(*value);
    }

    LObject* eval(Environment& env) throw (EvalException) {
        return env.lookup(*value);
    }

    ~LSymbol() {
        delete value;
    }

};

#endif // __LSYMBOL__

