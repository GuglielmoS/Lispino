#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include <string>
#include <map>

#include "LObject.h"

// builtin functions
class BuiltinFunction;

// arithmetics operators
#include "BuiltinSum.h"
#include "BuiltinSub.h"
#include "BuiltinMul.h"
#include "BuiltinDiv.h"

// booleans and equality operators
#include "BuiltinEqual.h"

// list operators
#include "BuiltinCar.h"
#include "BuiltinCdr.h"

class Environment {

    std::map<std::string, LObject*> symbolsTable;

    static std::map<std::string, BuiltinFunction*> initializeBuiltins() {
        std::map<std::string, BuiltinFunction*> m;
        
        // arithmetics
        m["+"] = new BuiltinSum();
        m["-"] = new BuiltinSub();
        m["*"] = new BuiltinMul();
        m["/"] = new BuiltinDiv();

        // equality and booleans
        m["="] = new BuiltinEqual();

        // list 
        m["car"] = new BuiltinCar();
        m["cdr"] = new BuiltinCdr();

        return m;
    }

    static std::map<std::string, BuiltinFunction*> builtinFunctions;

public:

    std::map<std::string, LObject*>* getSymbolsTable() {
        return &symbolsTable;
    }

    static BuiltinFunction* lookupBuiltinFunction(std::string& funcName);

    LObject* lookup(std::string& sym);
    LObject* lookup(std::string* sym);
    LObject* bind(std::string& sym, LObject* value);

    Environment* extendsWith(Environment& env) const;

    ~Environment();
};

#endif // __ENVIRONMENT_H__
