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
    
    class Environment {   

        Environment *enclosingEnv;
        std::unordered_map<std::string, std::pair<Symbol*, Object*>> frame;

        // builtin functions
        static std::unordered_map<std::string, std::unique_ptr<BuiltinFunction>> builtinFunctions;

        public:

            static std::unordered_map<std::string, std::unique_ptr<BuiltinFunction>> initializeBuiltinFunctions();

            Environment() : enclosingEnv(nullptr) {}
            Environment(Environment* env) : enclosingEnv(env) {}

            inline std::unordered_map<std::string, std::pair<Symbol*, Object*>>& lookupTable() {
                return frame;
            }

            inline std::unordered_map<std::string, std::pair<Symbol*, Object*>>::iterator iterator() {
                return frame.begin(); 
            }

            Object* update(Symbol* key, Object* value);
            Object* put(Symbol* key, Object* value);
            Object* get(Symbol* key);

    };
};

#endif // __ENVIRONMENT_H__
