#ifndef __BUILTIN_PRODUCT__

#define __BUILTIN_PRODUCT__

#include <vector>

#include "LObject.h"
#include "LNilObject.h"
#include "LInteger.h"
#include "LDouble.h"
#include "LSymbol.h"
#include "BuiltinFunction.h"

using namespace std;

class BuiltinProduct : public BuiltinFunction {
    
public:

    BuiltinProduct(const string& name) : BuiltinFunction(name) {}
    
    LObject* apply(vector<LObject*>& operands);

};

#endif // __BUILTIN_PRODUCT__

