#ifndef __BUILTIN_DECREMENT__

#define __BUILTIN_DECREMENT__

#include <vector>

#include "LObject.h"
#include "LNilObject.h"
#include "LInteger.h"
#include "LDouble.h"
#include "LSymbol.h"
#include "BuiltinFunction.h"

using namespace std;

class BuiltinDecrement : public BuiltinFunction {
    
public:

    BuiltinDecrement(const string& name) : BuiltinFunction(name) {}
    
    LObject* apply(vector<LObject*>& operands);

};

#endif // __BUILTIN_DECREMENT__


