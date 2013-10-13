#ifndef __MALFORMED_IF_EXCEPTION_H__
#define __MALFORMED_IF_EXCEPTION_H__

#include "ParserException.h"

class MalformedIfException : public ParserException {

    virtual const char* what() const throw() {
        return "Malformed IF expression";
    }

};

#endif // __MALFORMED_IF_EXCEPTION_H__
