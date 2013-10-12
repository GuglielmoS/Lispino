#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include <string>
#include <map>

#include "LObject.h"

// builtin functions
class BuiltinFunction;

#include "BuiltinSum.h"
#include "BuiltinSub.h"

class Environment {

    std::map<std::string, LObject*> symbolsTable;

    static std::map<std::string, BuiltinFunction*> initializeBuiltins() {
        std::map<std::string, BuiltinFunction*> m;
        m["+"] = new BuiltinSum();
        m["-"] = new BuiltinSub();
        //m[5] = 6;
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
