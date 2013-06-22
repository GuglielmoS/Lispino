#ifndef __INVALID_ARGUMENT_EXCEPTION__ 

#define __INVALID_ARGUMENT_EXCEPTION__

#include "EnvironmentException.h"

class InvalidArgumentException : public EnvironmentException {

    virtual const char* what() const throw() {
        return "invalid argument exception";
    }

};

#endif // __INVALID_ARGUMENT_EXCEPTION__


