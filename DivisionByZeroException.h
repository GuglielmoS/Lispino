#ifndef __DIVISION_BY_ZERO_EXCEPTION__ 
#define __DIVISION_BY_ZERO_EXCEPTION__

#include "EvalException.h"

class DivisionByZeroException : public EvalException {

    virtual const char* what() const throw() {
        return "Division by zero!";
    }

};

#endif // __DIVISION_BY_ZERO_EXCEPTION__


