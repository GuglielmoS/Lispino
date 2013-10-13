#ifndef __LOBJECT_H__
#define __LOBJECT_H__

// c++
#include <iostream>
#include <string>

// lisp types
#include "LType.h"

// execptions
#include "EvalException.h"

// used by the eval method
class Environment;

/**
 * This represent the element at the top of the lisp objects hierarchy.
 * Here are defined the methods which every lisp object must implement.
 */
class LObject {

public:
    
    virtual LType getType() const = 0;

    /**
     * Type checking.
     */

    // generic atom type
    bool isAtom() const {
        return isString()  or isSymbol()  or
               isInteger() or isDouble();
    }

    // specific types
    bool isString()          const { return getType() == ATOM_STRING;       }
    bool isSymbol()          const { return getType() == ATOM_SYMBOL;       }
    bool isDouble()          const { return getType() == ATOM_DOUBLE;       }
    bool isInteger()         const { return getType() == ATOM_INTEGER;      }
    bool isCons()            const { return getType() == CONS;              }
    bool isLambda()          const { return getType() == LAMBDA_EXPRESSION; }
    bool isIf()              const { return getType() == IF_EXPRESSION;     }
    bool isQuote()           const { return getType() == QUOTE_EXPRESSION;  }
    bool isBuiltinFunction() const { return getType() == BUILTIN_FUNCTION;  }
    bool isClosure()         const { return getType() == CLOSURE;           }

    // this is virtual for allowing the Cons object to be identified as NIL
    // when it is empty
    virtual bool isNIL() const {
        return getType() == NIL;
    }

    /**
     * Equality tests.
     */
    virtual bool equals(const LObject* otherObj) const {
        return this == otherObj;
    }

    /**
     * String representation.
     */
    virtual std::string prettyString() const = 0;

    /**
     * Evaluation.
     */
    virtual LObject* eval(Environment& env) throw (EvalException) = 0;
    
    /**
     * Helper for showing LObject's in streams.
     */
    friend std::ostream& operator<<(std::ostream& out, LObject* obj) {
        out << obj->prettyString();
        return out;
    }

    // destructor to redefine
    virtual ~LObject() {};
};

#endif // __LOBJECT_H__
