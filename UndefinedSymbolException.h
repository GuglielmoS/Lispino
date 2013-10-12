#ifndef __UNDEFINED_SYMBOL_EXCEPTION__

#define __UNDEFINED_SYMBOL_EXCEPTION__

#include <sstream>
#include "EvalException.h"

using namespace std;

class UndefinedSymbolException : public EvalException {

    virtual const char* what() const throw() {
        return "Undefined symbol";
    }

};

#endif // __UNDEFINED_SYMBOL_EXCEPTION__
