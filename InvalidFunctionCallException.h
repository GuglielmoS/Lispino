#ifndef __INVALID_FUNCTION_CALL_EXCEPTION__ 

#define __INVALID_FUNCTION_CALL_EXCEPTION__

#include "EnvironmentException.h"

class InvalidFunctionCallException : public EnvironmentException {

    virtual const char* what() const throw() {
        return "invalid function call";
    }

};

#endif // __INVALID_FUNCTION_CALL_EXCEPTION__



