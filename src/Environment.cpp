#include "Environment.h"

#include "builtin/Car.h"
#include "builtin/Cdr.h"
#include "builtin/Cons.h"
#include "builtin/Add.h"
#include "builtin/Sub.h"
#include "builtin/Mul.h"
#include "builtin/Div.h"
#include "builtin/Remainder.h"
#include "builtin/Display.h"
#include "builtin/Newline.h"
#include "builtin/Equal.h"
#include "builtin/GreaterThan.h"

using namespace Lispino;

std::map<std::string, std::unique_ptr<BuiltinFunction>> Environment::builtinFunctions = Environment::initializeBuiltinFunctions();

std::map<std::string, std::unique_ptr<BuiltinFunction>> Environment::initializeBuiltinFunctions() {
    std::map<std::string, std::unique_ptr<BuiltinFunction>> bindings;

    bindings["car"]       = std::unique_ptr<BuiltinFunction>(new BuiltinCar());
    bindings["cdr"]       = std::unique_ptr<BuiltinFunction>(new BuiltinCdr());
    bindings["cons"]      = std::unique_ptr<BuiltinFunction>(new BuiltinCons());
    bindings["+"]         = std::unique_ptr<BuiltinFunction>(new BuiltinAdd());
    bindings["-"]         = std::unique_ptr<BuiltinFunction>(new BuiltinSub());
    bindings["*"]         = std::unique_ptr<BuiltinFunction>(new BuiltinMul());
    bindings["/"]         = std::unique_ptr<BuiltinFunction>(new BuiltinDiv());
    bindings["remainder"] = std::unique_ptr<BuiltinFunction>(new BuiltinRemainder());
    bindings["="]         = std::unique_ptr<BuiltinFunction>(new BuiltinEqual());
    bindings[">"]         = std::unique_ptr<BuiltinFunction>(new BuiltinGreaterThan());
    bindings["display"]   = std::unique_ptr<BuiltinFunction>(new BuiltinDisplay());
    bindings["newline"]   = std::unique_ptr<BuiltinFunction>(new BuiltinNewline());

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
