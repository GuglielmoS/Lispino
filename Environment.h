#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include <string>
#include <map>

#include "LObject.h"
#include "UndefinedSymbolException.h"

class Environment {

    std::map<std::string, LObject*> symbolsTable;

public:

    LObject* lookup(std::string& sym);
    LObject* lookup(std::string* sym);
    LObject* bind(std::string& sym, LObject* value);

    Environment* extendsWith(Environment& env) const;

    ~Environment();
};

#endif // __ENVIRONMENT_H__
