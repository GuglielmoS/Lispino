#ifndef __EMPTY_EXPRESSION_EXCEPTION__

#define __EMPTY_EXPRESSION_EXCEPTION__

#include "ParserException.h"

class EmptyExpressionException : public ParserException {

    virtual const char* what() const throw() {
        return "An empty expression cannot be parsed";
    }

};

#endif // __EMPTY_EXPRESSION_EXCEPTION__

