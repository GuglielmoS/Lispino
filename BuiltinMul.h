#ifndef __BUILTIN_MUL_H__
#define __BUILTIN_MUL_H__

#include "BuiltinFunction.h"

class BuiltinMul : public BuiltinFunction {

public:

    std::string prettyString() const { return "#<BUILTIN-FUNCTION:MUL>"; }

    LObject* eval(LObject* args, Environment& env) const throw (EvalException);

};

#endif // __BUILTIN_MUL_H__
