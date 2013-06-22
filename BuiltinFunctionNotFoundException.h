#ifndef __BUILTIN_FUNCTION_NOT_FOUND_EXCEPTION__

#define __BUILTIN_FUNCTION_NOT_FOUND_EXCEPTION__

#include "EnvironmentException.h"

class BuiltinFunctionNotFoundException : public EnvironmentException {

    virtual const char* what() const throw() {
        return "builtin function not found";
    }

};

#endif // __BUILTIN_FUNCTION_NOT_FOUND_EXCEPTION__

