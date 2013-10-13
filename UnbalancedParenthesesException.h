#ifndef __UNBALANCED_PARENTHESES_EXCEPTION_H__
#define __UNBALANCED_PARENTHESES_EXCEPTION_H__

#include "ParserException.h"

class UnbalancedParenthesesException : public ParserException {

    virtual const char* what() const throw() {
        return "Unbalanced parentheses in the expression";
    }

};

#endif // __UNBALANCED_PARENTHESES_EXCEPTION_H__
