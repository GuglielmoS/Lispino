#ifndef __MALFORMED_DEFINE_EXCEPTION_H__
#define __MALFORMED_DEFINE_EXCEPTION_H__

#include "ParserException.h"

class MalformedDefineException : public ParserException {

    virtual const char* what() const throw() {
        return "Malformed DEF expression";
    }

};

#endif // __MALFORMED_DEFINE_EXCEPTION_H__
