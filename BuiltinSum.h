#ifndef __BUILTIN_SUM_H__
#define __BUILTIN_SUM_H__

#include "BuiltinFunction.h"

class BuiltinSum : public BuiltinFunction {

public:

    std::string prettyString() const { return "#<BUILTIN-FUNCTION:SUM>"; }

    LObject* eval(LObject* args, Environment& env) const throw (EvalException);

};

#endif // __BUILTIN_SUM_H__
