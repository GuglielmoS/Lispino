#ifndef __BUILTIN_CAR_H__
#define __BUILTIN_CAR_H__

#include "BuiltinFunction.h"

class BuiltinCar : public BuiltinFunction {

public:

    std::string prettyString() const { return "#<BUILTIN-FUNCTION:CAR>"; }
    
    LObject* eval(LObject* args, Environment& env) const throw (EvalException);

};

#endif // __BUILTIN_CAR_H__
