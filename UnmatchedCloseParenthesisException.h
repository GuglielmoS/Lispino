#ifndef __UNMATCHED_CLOSE_PARENTHESIS_H__
#define __UNMATCHED_CLOSE_PARENTHESIS_H__

#include "ParserException.h"

class UnmatchedCloseParenthesisException : public ParserException {

    virtual const char* what() const throw() {
        return "Unmatched close parenthesis";
    }

};

#endif // __UNMATCHED_CLOSE_PARENTHESIS_H__
