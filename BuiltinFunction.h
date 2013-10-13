#ifndef __BUILTIN_FUNCTION_H__
#define __BUILTIN_FUNCTION_H__

// lisp objects
#include "LObject.h"

// exceptions
#include "EvalException.h"

// used for the eval method
class Environment;

/**
 * This class represent how a Builtin Function must be implemented.
 */ 
class BuiltinFunction : public LObject {
    
public:
    
    LType getType() const { return BUILTIN_FUNCTION; }
   
    LObject* eval(Environment& env) throw (EvalException) {
        return this;
    }

    virtual LObject* eval(LObject* args, Environment& env) const throw (EvalException) = 0;

    virtual ~BuiltinFunction() {};
};

#endif // __BUILTIN_FUNCTION_H__
