#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include "Object.h"
#include "Symbol.h"
#include "builtin/BuiltinFunction.h"

#include <map>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iostream>
#include <memory>

namespace Lispino {
    
    class SymbolComparator {
        public:
            bool operator()(const Symbol* sym1, const Symbol* sym2) const {
                return sym1->getValue() < sym2->getValue();
            }
    };

    class Environment {   

        Environment *enclosingEnv;
        std::map<Symbol*, Object*, SymbolComparator> frame;

        // builtin functions
        static std::unordered_map<std::string, std::unique_ptr<BuiltinFunction>> builtinFunctions;

        public:

            static std::unordered_map<std::string, std::unique_ptr<BuiltinFunction>> initializeBuiltinFunctions();

            Environment() : enclosingEnv(nullptr) {}
            Environment(Environment* env) : enclosingEnv(env) {}

            inline std::map<Symbol*, Object*, SymbolComparator>* lookupTable() {
                return &frame;
            }

            inline std::map<Symbol*, Object*, SymbolComparator>::iterator iterator() {
                return frame.begin(); 
            }

            Object* update(Symbol* key, Object* value);
            Object* put(Symbol* key, Object* value);
            Object* get(Symbol* key);

    };
};

#endif // __ENVIRONMENT_H__
