#ifndef __BUILTIN_SUM__

#define __BUILTIN_SUM__

#include <vector>

#include "LObject.h"
#include "LNilObject.h"
#include "LInteger.h"
#include "LDouble.h"
#include "LSymbol.h"
#include "BuiltinFunction.h"

using namespace std;

class BuiltinSum : public BuiltinFunction {

public:

    BuiltinSum(const string& name) : BuiltinFunction(name) {}

    LObject* apply(vector<LObject*>& operands);

};

#endif // __BUILTIN_SUM__

