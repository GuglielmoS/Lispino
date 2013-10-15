#ifndef __BUILTIN_CONS_H__
#define __BUILTIN_CONS_H__

#include "BuiltinFunction.h"

class BuiltinCons : public BuiltinFunction {

public:

    std::string prettyString() const { return "#<BUILTIN-FUNCTION:CONS>"; }
    
    LObject* eval(LObject* args, Environment& env) const throw (EvalException);

};

#endif // __BUILTIN_CONS_H__
