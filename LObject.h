#ifndef __LOBJECT__
#define __LOBJECT__

#include <iostream>
#include <string>

#include "LType.h"
#include "EvalException.h"

class Environment;

class LObject {

public:
    
    bool isAtom() const {
        return isString()  or
               isSymbol()  or
               isInteger() or
               isDouble();
    }

    bool isString() const {
        return getType() == ATOM_STRING;
    }

    bool isSymbol() const {
        return getType() == ATOM_SYMBOL;
    }

    bool isDouble() const {
        return getType() == ATOM_DOUBLE;
    }

    bool isInteger() const {
        return getType() == ATOM_INTEGER;
    }

    bool isCons() const {
        return getType() == CONS;
    }

    bool isLambda() const {
        return getType() == LAMBDA_EXPRESSION;
    }

    bool isIf() const {
        return getType() == IF_EXPRESSION;
    }
    
    bool isQuote() const {
        return getType() == QUOTE_EXPRESSION;
    }

    bool isNIL() const {
        return getType() == NIL;
    }

    bool isBuiltinFunction() const {
        return getType() == BUILTIN_FUNCTION;
    }

    bool isClosure() const {
        return getType() == CLOSURE;
    }

    virtual bool equals(const LObject* otherObj) const {
        return this == otherObj;
    }

    virtual LType getType() const = 0;
    virtual std::string prettyString() const = 0;
    virtual LObject* eval(Environment& env) throw (EvalException) = 0;
    virtual ~LObject() {};
    
    friend std::ostream& operator<<(std::ostream& out, LObject* obj) {
        out << obj->prettyString();
        return out;
    }
};

#endif // __LOBJECT__
