#ifndef __MALFORMED_STRING_EXCEPTION__

#define __MALFORMED_STRING_EXCEPTION__

#include "TokenizerException.h"

class MalformedStringException : public TokenizerException {

    virtual const char* what() const throw() {
        return "Missing the End Of String character";
    }

};

#endif // __MALFORMED_STRING_EXCEPTION__

