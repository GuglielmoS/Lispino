#include "Environment.h"

#include "BuiltinCar.h"
#include "BuiltinCdr.h"
#include "BuiltinCons.h"
#include "BuiltinAdd.h"

using namespace Lispino;

std::map<std::string, std::unique_ptr<BuiltinFunction>> Environment::builtinFunctions = Environment::initializeBuiltinFunctions();

std::map<std::string, std::unique_ptr<BuiltinFunction>> Environment::initializeBuiltinFunctions() {
    std::map<std::string, std::unique_ptr<BuiltinFunction>> bindings;

    bindings["car"]  = std::unique_ptr<BuiltinFunction>(new BuiltinCar());
    bindings["cdr"]  = std::unique_ptr<BuiltinFunction>(new BuiltinCdr());
    bindings["cons"] = std::unique_ptr<BuiltinFunction>(new BuiltinCons());
    bindings["+"]  = std::unique_ptr<BuiltinFunction>(new BuiltinAdd());

    return bindings;
}

bool Environment::isBuiltinFunction(Symbol* symbol) {
    std::map<std::string, std::unique_ptr<BuiltinFunction>>::iterator iter;
    iter = builtinFunctions.find(symbol->getValue());
    return iter != builtinFunctions.end();
}

BuiltinFunction* Environment::getBuiltinFunction(Symbol* symbol) {
    std::map<std::string, std::unique_ptr<BuiltinFunction>>::iterator iter;
    iter = builtinFunctions.find(symbol->getValue());

    if (iter != builtinFunctions.end())
        return iter->second.get();
    
    throw std::out_of_range("Invalid builtin function: " + symbol->toString());
}
