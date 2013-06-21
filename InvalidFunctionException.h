#ifndef __INVALID_FUNCTION_EXCEPTION__

#define __INVALID_FUNCTION_EXCEPTION__

#include "EnvironmentException.h"

class InvalidFunctionException : public EnvironmentException {

    virtual const char* what() const throw() {
        return "invalid function definition";
    }

};

#endif // __INVALID_FUNCTION_EXCEPTION__


