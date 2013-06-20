#ifndef __LENVIRONMENT__

#define __LENVIRONMENT__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#include "LObject.h"
#include "LNilObject.h"
#include "LAtom.h"
#include "LCons.h"
#include "LInteger.h"
#include "LSymbol.h"
#include "Parser.h"
#include "BuiltinFunction.h"
#include "BuiltinSum.h"
#include "BuiltinProduct.h"
#include "BuiltinDecrement.h"
#include "LLambda.h"

using namespace std;

class Environment {
    
    vector<BuiltinFunction*> builtinFunctions;
    map<string,LObject*> symTable;
    Environment *parent;

    // builtin functions helpers
    void addBuiltinFunctions();
    BuiltinFunction* findBuiltinFunc(const string& funcName) const;

    // environment helpers
    bool applyEnv(vector<LObject*>& args);
    void extractArguments(const LCons *operands, vector<LObject*>& args, bool withEval=true);

    // evaluation methods
    LObject* evalExpr(LObject *expr);
    LObject* evalAtom(LAtom *expr);
    LObject* evalCons(LCons *expr);

    // special definitions
    LObject* define(LCons *args, LObject *body);
    LObject* defineFunction(LCons *funcArgs, LObject *body);
    LObject* defineSymbol(LSymbol *symbol, LObject *value);

public:

    Environment() : parent(0) {
        addBuiltinFunctions();
    }

    Environment(Environment *parent) : parent(parent) {
        addBuiltinFunctions();
    }

    void setParentEnv(Environment* env);

    void bind(LSymbol* symName, LObject* value);
    LObject* valueOf(LSymbol* symbol);

    LObject* eval(string& inputExpr);
    LObject* eval(LObject* expr);
    
    virtual ~Environment();
};

#endif // __LENVIRONMENT__


