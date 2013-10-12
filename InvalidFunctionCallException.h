#ifndef __INVALID_FUNCTION_CALL_EXCEPTION__ 

#define __INVALID_FUNCTION_CALL_EXCEPTION__

#include "EvalException.h"

class InvalidFunctionCallException : public EvalException {

    virtual const char* what() const throw() {
        return "Invalid function call";
    }

};

#endif // __INVALID_FUNCTION_CALL_EXCEPTION__



