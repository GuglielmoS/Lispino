#ifndef __UNDEFINED_FUNCTION_EXCEPTION__

#define __UNDEFINED_FUNCTION_EXCEPTION__

#include <iostream>

#include "EnvironmentException.h"

using namespace std;

class UndefinedFunctionException : public EnvironmentException {

    /*const string functionName;

    UndefinedFunctionException(const string& str) : functionName(string(str)) {} 
    */
        
    virtual const char* what() const throw() {
        /*
        stringstream ss;
        ss <<"\"" + functionName + "\" - undefined function";

        return ss.str().c_str();
        */

        return "undefined function";
    }

};

#endif // __UNDEFINED_FUNCTION_EXCEPTION__
