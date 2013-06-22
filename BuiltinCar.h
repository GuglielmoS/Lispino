#ifndef __BUILTIN_CAR__

#define __BUILTIN_CAR__

#include <vector>

#include "LObject.h"
#include "LNilObject.h"
#include "LInteger.h"
#include "LDouble.h"
#include "LSymbol.h"
#include "BuiltinFunction.h"

using namespace std;

class BuiltinCar : public BuiltinFunction {
    
public:

    BuiltinCar(const string& name) : BuiltinFunction(name) {}
    
    LObject* apply(vector<LObject*>& operands);

};

#endif // __BUILTIN_PRODUCT__


