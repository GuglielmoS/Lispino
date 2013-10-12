#ifndef __MALFORMED_LAMBDA_EXCEPTION__
#define __MALFORMED_LAMBDA_EXCEPTION__

#include "ParserException.h"

class MalformedLambdaException : public ParserException {

    virtual const char* what() const throw() {
        return "Malformed LAMBDA expression";
    }

};

#endif // __MALFORMED_LAMBDA_EXCEPTION__

