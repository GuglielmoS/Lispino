#ifndef LISPINO_ENVIRONMENT_H_
#define LISPINO_ENVIRONMENT_H_

#include <map>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iostream>
#include <memory>

#include "Object.h"
#include "Symbol.h"
#include "builtin/BuiltinFunction.h"

namespace Lispino {
    
    class Environment {   

        Environment *enclosingEnv;
        std::unordered_map<std::string, std::pair<Symbol*, Object*>> frame;

        // builtin functions
        static std::unordered_map<std::string, std::unique_ptr<BuiltinFunction>> builtinFunctions;
        static std::unordered_map<std::string, std::unique_ptr<BuiltinFunction>> initializeBuiltinFunctions();

        public:
            
            Environment() : enclosingEnv(nullptr) {}
            Environment(Environment* env) : enclosingEnv(env) {}

            Environment* getParent() {
                return enclosingEnv;
            }

            void setParent(Environment *env) {
                this->enclosingEnv = env;
            }

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

#endif // LISPINO_ENVIRONMENT_H_
