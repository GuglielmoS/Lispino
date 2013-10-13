#ifndef __BUILTIN_DIV_H__
#define __BUILTIN_DIV_H__

#include "BuiltinFunction.h"

class BuiltinDiv : public BuiltinFunction {

public:

    std::string prettyString() const { return "#<BUILTIN-FUNCTION:DIV>"; }

    LObject* eval(LObject* args, Environment& env) const throw (EvalException);

};

#endif // __BUILTIN_DIV_H__
