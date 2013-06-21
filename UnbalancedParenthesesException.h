#ifndef __UNBALANCED_PARENTHESES_EXCEPTION__

#define __UNBALANCED_PARENTHESES_EXCEPTION__

#include "ParserException.h"

class UnbalancedParenthesesException : public ParserException {

    virtual const char* what() const throw() {
        return "Unbalanced parentheses in the expression";
    }

};

#endif // __UNBALANCED_PARENTHESES_EXCEPTION__
