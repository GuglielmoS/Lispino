#ifndef __UNDEFINED_BUILTIN_FUNCTION_EXCEPTION_H__
#define __UNDEFINED_BUILTIN_FUNCTION_EXCEPTION_H__

#include "EvalException.h"

class UndefinedBuiltinFunctionException : public EvalException {

    virtual const char* what() const throw() {
        return "Undefined builtin function";
    }

};

#endif // __UNDEFINED_BUILTIN_FUNCTION_EXCEPTION_H__
