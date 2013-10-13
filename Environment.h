#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

// c++
#include <string>
#include <map>

// lisp objects
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

/**
 * This class represents a generic environment in which objects can be stored.
 * It exposes the methods 'lookup' and 'bind' for getting and putting objects
 * respectively.
 * The method 'extendsWith' is a helper that merges the current environment with
 * another one, and then return the pointer to the created environment.
 *
 * Since there can be several objects which are predefined and don't need to be
 * duplicated in every environment, there is a static map which allow the storing
 * of these kind of objects (BuiltinFunctions).
 */
class Environment {

    std::map<std::string, LObject*> symbolsTable;

    /**
     * Initializes a map with the builtin functions and then returns it.
     */
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
