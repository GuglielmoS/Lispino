#ifndef __BUILTIN_CDR__

#define __BUILTIN_CDR__

#include <vector>

#include "LObject.h"
#include "LNilObject.h"
#include "LInteger.h"
#include "LDouble.h"
#include "LSymbol.h"
#include "BuiltinFunction.h"

using namespace std;

class BuiltinCdr : public BuiltinFunction {
    
public:

    BuiltinCdr(const string& name) : BuiltinFunction(name) {}
    
    LObject* apply(vector<LObject*>& operands);

};

#endif // __BUILTIN_PRODUCT__



