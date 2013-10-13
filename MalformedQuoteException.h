#ifndef __MALFORMED_QUOTE_EXCEPTION_H__
#define __MALFORMED_QUOTE_EXCEPTION_H__

#include "ParserException.h"

class MalformedQuoteException : public ParserException {

    virtual const char* what() const throw() {
        return "Malformed quotation";
    }

};

#endif // __MALFORMED_QUOTE_EXCEPTION_H__
