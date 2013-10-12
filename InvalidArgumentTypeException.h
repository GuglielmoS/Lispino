#ifndef __INVALID_ARGUMENT_TYPE_EXCEPTION__ 

#define __INVALID_ARGUMENT_TYPE_EXCEPTION__

#include "EvalException.h"

class InvalidArgumentTypeException : public EvalException {

    virtual const char* what() const throw() {
        return "Invalid argument type exception";
    }

};

#endif // __INVALID_ARGUMENT_TYPE_EXCEPTION__


