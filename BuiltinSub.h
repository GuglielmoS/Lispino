#ifndef __BUILTIN_SUB_H__
#define __BUILTIN_SUB_H__

#include "BuiltinFunction.h"

class BuiltinSub : public BuiltinFunction {

public:

    LObject* eval(LObject* args, Environment& env) const throw (EvalException);

};

#endif // __BUILTIN_SUB_H__
