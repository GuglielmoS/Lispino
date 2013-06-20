#ifndef __BUILTIN_FUNCTION__

#define __BUILTIN_FUNCTION__

#include "LObject.h"
#include "LSymbol.h"
#include "LCons.h"

class BuiltinFunction {

    LSymbol *name;

public:
    
    BuiltinFunction(const string& name) : name(new LSymbol(name)) {}
    
    LSymbol* getSymbol() {
        return name;
    }

    string getName() {
        return name->getValue();
    }

    virtual LObject* apply(vector<LObject*>& arguments) = 0;

    virtual ~BuiltinFunction() {
        delete name;
    }
};

#endif // __BUILTIN_FUNCTION__
