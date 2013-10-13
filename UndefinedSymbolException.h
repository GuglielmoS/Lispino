#ifndef __UNDEFINED_SYMBOL_EXCEPTION_H__
#define __UNDEFINED_SYMBOL_EXCEPTION_H__

#include "EvalException.h"

class UndefinedSymbolException : public EvalException {

    virtual const char* what() const throw() {
        return "Undefined symbol";
    }

};

#endif // __UNDEFINED_SYMBOL_EXCEPTION_H__
