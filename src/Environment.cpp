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

Object* Environment::update(Symbol* key, Object* value) {
    std::map<Symbol*,Object*,SymbolComparator>::iterator iter = frame.find(key);
    
    if (iter == frame.end()) {
        if (enclosingEnv != nullptr)
            enclosingEnv->update(key, value);
        else
            throw std::out_of_range("Environment update failed with key: " + key->toString());
    } else
        frame[key] = value;

    return value;
}

Object* Environment::put(Symbol* key, Object* value) {
    frame[key] = value;

    return value;
}

Object* Environment::get(Symbol* key) {
    // check for builtin functions
    std::map<std::string, std::unique_ptr<BuiltinFunction>>::iterator bf_iter = builtinFunctions.find(key->getValue());
    if (bf_iter != builtinFunctions.end())
        return bf_iter->second.get();

    // check for environment values
    std::map<Symbol*,Object*,SymbolComparator>::iterator iter = frame.find(key);
    if (iter == frame.end()) {
        if (enclosingEnv != nullptr)
            return enclosingEnv->get(key);

        throw std::out_of_range("Environment lookup failed with key: " + key->toString());
    }

    return iter->second;
}
