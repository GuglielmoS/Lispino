#include "Environment.h"

#include "builtins/Car.h"
#include "builtins/Cdr.h"
#include "builtins/Cons.h"
#include "builtins/Add.h"
#include "builtins/Sub.h"
#include "builtins/Mul.h"
#include "builtins/Div.h"
#include "builtins/Remainder.h"
#include "builtins/Display.h"
#include "builtins/Newline.h"
#include "builtins/Equal.h"
#include "builtins/GreaterThan.h"
#include "builtins/GreaterEqualThan.h"
#include "builtins/LowerThan.h"
#include "builtins/LowerEqualThan.h"

namespace Lispino {

    // initialize the builtin functions
    std::unordered_map<std::string, std::unique_ptr<Builtins::BuiltinFunction>> 
        Environment::builtinFunctions = Environment::initializeBuiltinFunctions();

    Environment::Environment() : enclosingEnv(nullptr) {
        /* DO NOTHING */
    }

    Environment::Environment(Environment* env) : enclosingEnv(env) {
        /* DO NOTHING */
    }

    Environment* Environment::getParent() {
        return enclosingEnv;
    }

    void Environment::setParent(Environment *env) {
        this->enclosingEnv = env;
    }

    std::unordered_map<std::string, std::pair<Symbol*, Object*>>& Environment::lookupTable() {
        return frame;
    }

    std::unordered_map<std::string, std::pair<Symbol*, Object*>>::iterator Environment::iterator() {
        return frame.begin(); 
    }

    Object* Environment::update(Symbol* key, Object* value) {
        auto iter = frame.find(key->getValue());
        
        if (iter == frame.end()) {
            if (enclosingEnv != nullptr) {
                enclosingEnv->update(key, value);
            } else {
                throw std::out_of_range("Environment update failed with key: " + key->toString());
            }
        } else {
            frame[key->getValue()] = std::make_pair(key,value);
        }

        return value;
    }

    Object* Environment::put(Symbol* key, Object* value) {
        frame[key->getValue()] = std::make_pair(key,value);

        return value;
    }

    Object* Environment::get(Symbol* key) {
        // check for builtin functions
        auto bf_iter = builtinFunctions.find(key->getValue());

        if (bf_iter != builtinFunctions.end())
            return bf_iter->second.get();

        // check for environment values
        auto iter = frame.find(key->getValue());
        if (iter != frame.end())
            return (iter->second).second;

        // check in the parent environment
        if (enclosingEnv != nullptr)
            return enclosingEnv->get(key);

        // the lookup has failed, thus signal an error
        throw std::out_of_range("Environment lookup failed with [key = " + key->toString() + "]");
    }

    std::unordered_map<std::string, std::unique_ptr<Builtins::BuiltinFunction>> Environment::initializeBuiltinFunctions() {
        std::unordered_map<std::string, std::unique_ptr<Builtins::BuiltinFunction>> bindings;

        // list
        bindings["car"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::Car());
        bindings["cdr"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::Cdr());
        bindings["cons"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::Cons());

        // maths
        bindings["+"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::Add());
        bindings["-"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::Sub());
        bindings["*"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::Mul());
        bindings["/"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::Div());
        bindings["remainder"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::Remainder());

        // equality
        bindings["="] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::Equal());
        bindings[">"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::GreaterThan());
        bindings[">="] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::GreaterEqualThan());
        bindings["<"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::LowerThan());
        bindings["<="] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::LowerEqualThan());

        // I/O utils
        bindings["display"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::Display());
        bindings["newline"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::Newline());

        return bindings;
    }
}
