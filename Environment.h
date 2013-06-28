#ifndef __LENVIRONMENT__

#define __LENVIRONMENT__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

// objects
#include "LObject.h"
#include "LNilObject.h"
#include "LAtom.h"
#include "LCons.h"
#include "LInteger.h"
#include "LSymbol.h"
#include "LLambda.h"

// parsing
#include "Parser.h"

// builtin functions
#include "BuiltinFunction.h"
#include "BuiltinSum.h"
#include "BuiltinProduct.h"
#include "BuiltinDecrement.h"
#include "BuiltinCar.h"
#include "BuiltinCdr.h"

// exceptions
#include "LispinoException.h"
#include "EnvironmentException.h"
#include "UndefinedSymbolException.h"
#include "UndefinedFunctionException.h"
#include "InvalidQuoteException.h"
#include "InvalidFunctionException.h"
#include "BuiltinFunctionNotFoundException.h"
#include "InvalidArgumentException.h"
#include "InvalidFunctionCallException.h"

using namespace std;

class Environment {
    
    // container for the builtin functions
    vector<BuiltinFunction*> builtinFunctions;

    // symbols table for storing the variables and functions
    // defined at runtime
    map<string,LObject*> symTable;

    // the father environment
    Environment *parent;

    /**
     * Private methods.
     */

    // builtin functions helpers
    void addBuiltinFunctions();

    // environment helpers
    void applyEnv(vector<LObject*>& args) throw (EnvironmentException);
    void extractArguments(const LCons *operands, vector<LObject*>& args, bool withEval=true) throw (EnvironmentException);

    // evaluation methods
    LObject* evalExpr(LObject *expr) throw (EnvironmentException);
    LObject* evalAtom(LAtom *expr) throw (EnvironmentException);
    LObject* evalCons(LCons *expr) throw (EnvironmentException);

    // functions application
    LObject* tryFunctionApplication(LSymbol *symbol, LCons *operands) throw (EnvironmentException);
    LObject* tryLambda(LSymbol* symbol, LCons *operands) throw (EnvironmentException);
    LObject* tryBuiltinFunction(LSymbol *symbol, LCons *operands) throw (EnvironmentException);

    // special definitions
    LObject* define(LCons *args, LObject *body) throw (EnvironmentException);
    LSymbol* defineFunction(LCons *funcArgs, LObject *body) throw (EnvironmentException);
    LSymbol* defineSymbol(LSymbol *symbol, LObject *value) throw (EnvironmentException);
    LLambda* defineLambda(LCons* operands, LCons* body) throw (EnvironmentException);
    LObject* quote(LCons* operands) throw (EnvironmentException);

protected:

    // method for searching builtin functions
    BuiltinFunction* findBuiltinFunc(const string& funcName) const throw (EnvironmentException);

public:

    Environment();
    Environment(Environment *parent);

    // setter for the father environment
    void setParentEnv(Environment* env);

    // setter and getter for the symbols table
    void bind(LSymbol* symName, LObject* value);
    LObject* valueOf(LSymbol* symbol) throw (EnvironmentException);

    // evaluation methods
    LObject* eval(string& inputExpr) throw (LispinoException);
    LObject* eval(LObject* expr) throw (LispinoException);
    
    virtual ~Environment();
};

#endif // __LENVIRONMENT__


