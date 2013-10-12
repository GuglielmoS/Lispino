#include "Environment.h"

Environment* Environment::extendsWith(Environment& env) const {
    Environment *finalEnv = new Environment();

    finalEnv->symbolsTable.insert(env.symbolsTable.begin(), env.symbolsTable.end());
    finalEnv->symbolsTable.insert(symbolsTable.begin(), symbolsTable.end());

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
    symbolsTable[symbol] = value;

    return value;
}

Environment::~Environment()  {
    symbolsTable.clear();
}
