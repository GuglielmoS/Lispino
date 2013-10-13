#ifndef __BUILTIN_EQUAL_H__
#define __BUILTIN_EQUAL_H__

#include "BuiltinFunction.h"

class BuiltinEqual : public BuiltinFunction {

public:

    std::string prettyString() const { return "#<BUILTIN-FUNCTION:EQUAL>"; }

    LObject* eval(LObject* args, Environment& env) const throw (EvalException);

};

#endif // __BUILTIN_EQUAL_H__
