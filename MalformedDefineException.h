#ifndef __MALFORMED_DEFINE_EXCEPTION__
#define __MALFORMED_DEFINE_EXCEPTION__

#include "ParserException.h"

class MalformedDefineException : public ParserException {

    virtual const char* what() const throw() {
        return "Malformed DEF expression";
    }

};

#endif // __MALFORMED_DEFINE_EXCEPTION__

