#ifndef __BUILTIN_FUNCTION_H__
#define __BUILTIN_FUNCTION_H__

#include "LObject.h"

#include "EvalException.h"

class Environment;

class BuiltinFunction : public LObject {
    
public:
    LType getType() const {
        return BUILTIN_FUNCTION;
    }
    
    std::string prettyString() const {
        return "#BUILTIN-FUNCTION";
    }

    LObject* eval(Environment& env) throw (EvalException) {
        return this;
    }

    virtual LObject* eval(LObject* args, Environment& env) const throw (EvalException) = 0;

    ~BuiltinFunction() {};
};

#endif // __BUILTIN_FUNCTION_H__
