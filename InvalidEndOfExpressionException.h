#ifndef __INVALID_END_OF_EXPRESSION_EXCEPTION_H__
#define __INVALID_END_OF_EXPRESSION_EXCEPTION_H__

#include "ParserException.h"

class InvalidEndOfExpressionException : public ParserException {

    virtual const char* what() const throw() {
        return "Invalid End Of Expression found";
    }

};

#endif // __INVALID_END_OF_EXPRESSION_EXCEPTION_H__


