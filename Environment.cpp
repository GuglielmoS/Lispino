#include "Environment.h"

// exceptions
#include "UndefinedSymbolException.h"
#include "UndefinedBuiltinFunctionException.h"

std::map<std::string, BuiltinFunction*> Environment::builtinFunctions = Environment::initializeBuiltins();

BuiltinFunction* Environment::lookupBuiltinFunction(std::string& funcName) {
    std::map<std::string, BuiltinFunction*>::iterator it = builtinFunctions.find(funcName);
    
    if (it != builtinFunctions.end())
        return it->second;

    throw UndefinedBuiltinFunctionException();
}

Environment* Environment::extendsWith(Environment& env) const {
    Environment *finalEnv = new Environment();

    finalEnv->symbolsTable.insert(symbolsTable.begin(), symbolsTable.end());
    finalEnv->symbolsTable.insert(env.symbolsTable.begin(), env.symbolsTable.end());

    return finalEnv;
}

LObject* Environment::lookup(std::string& symName) {
    std::map<std::string, LObject*>::iterator it = symbolsTable.find(symName);
    
    if (it != symbolsTable.end())
        return it->second;
        
    throw UndefinedSymbolException();
}

LObject* Environment::lookup(std::string* symbol) {
    if (symbol != 0)
        return lookup(*symbol);
    
    throw UndefinedSymbolException();
}

LObject* Environment::bind(std::string& symbol, LObject* value) {
    try {
        LObject* oldValue = lookup(symbol);
        delete oldValue;
    } catch (UndefinedSymbolException& e) { /* DO NOTHING */ }

    symbolsTable[symbol] = value;

    return value;
}

Environment::~Environment()  {
    symbolsTable.clear();
}
