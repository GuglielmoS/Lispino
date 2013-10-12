#ifndef __MALFORMED_IF_EXCEPTION__
#define __MALFORMED_IF_EXCEPTION__

#include "ParserException.h"

class MalformedIfException : public ParserException {

    virtual const char* what() const throw() {
        return "Malformed IF expression";
    }

};

#endif // __MALFORMED_IF_EXCEPTION__

