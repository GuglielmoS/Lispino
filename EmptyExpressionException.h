#ifndef __EMPTY_EXPRESSION_EXCEPTION_H__
#define __EMPTY_EXPRESSION_EXCEPTION_H__

#include "ParserException.h"

class EmptyExpressionException : public ParserException {

    virtual const char* what() const throw() {
        return "An empty expression cannot be parsed";
    }

};

#endif // __EMPTY_EXPRESSION_EXCEPTION_H__

