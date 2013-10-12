#ifndef __UNDEFINED_BUILTIN_FUNCTION_EXCEPTION__

#define __UNDEFINED_BUILTIN_FUNCTION_EXCEPTION__

#include <sstream>
#include "EvalException.h"

using namespace std;

class UndefinedBuiltinFunctionException : public EvalException {

    virtual const char* what() const throw() {
        return "Undefined builtin function";
    }

};

#endif // __UNDEFINED_BUILTIN_FUNCTION_EXCEPTION__
