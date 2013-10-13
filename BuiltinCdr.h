#ifndef __BUILTIN_CDR_H__
#define __BUILTIN_CDR_H__

#include "BuiltinFunction.h"

class BuiltinCdr : public BuiltinFunction {

public:

    std::string prettyString() const { return "#<BUILTIN-FUNCTION:CDR>"; }

    LObject* eval(LObject* args, Environment& env) const throw (EvalException);

};

#endif // __BUILTIN_CDR_H__
