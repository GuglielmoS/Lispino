#ifndef __INVALID_QUOTE_EXCEPTION__

#define __INVALID_QUOTE_EXCEPTION__

#include "EnvironmentException.h"

class InvalidQuoteException : public EnvironmentException {

    virtual const char* what() const throw() {
        return "invalid quotation";
    }

};

#endif // __INVALID_QUOTE_EXCEPTION__

