#ifndef __UNDEFINED_SYMBOL_EXCEPTION__

#define __UNDEFINED_SYMBOL_EXCEPTION__

#include <sstream>
#include "EnvironmentException.h"

using namespace std;

class UndefinedSymbolException : public EnvironmentException {

    /*
    const string symbolName;

    UndefinedSymbolException() : symbolName("") {}
    UndefinedSymbolException(const string& str) : symbolName(string(str)) {} 
    */

    virtual const char* what() const throw() {
        /*
        stringstream ss;
        ss <<"\"" + symbolName + "\" - undefined symbol";

        return ss.str().c_str();
        */

        return "undefined symbol";
    }

};

#endif // __UNDEFINED_SYMBOL_EXCEPTION__
