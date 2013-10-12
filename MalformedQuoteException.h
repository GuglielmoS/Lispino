#ifndef __MALFORMED_QUOTE_EXCEPTION__
#define __MALFORMED_QUOTE_EXCEPTION__

#include "ParserException.h"

class MalformedQuoteException : public ParserException {

    virtual const char* what() const throw() {
        return "Malformed quotation";
    }

};

#endif // __MALFORMED_QUOTE_EXCEPTION__

