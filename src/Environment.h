#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include "Object.h"
#include "Symbol.h"
#include "BuiltinFunction.h"

#include <map>
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
        static std::map<std::string, std::unique_ptr<BuiltinFunction>> builtinFunctions;

        public:

            static std::map<std::string, std::unique_ptr<BuiltinFunction>> initializeBuiltinFunctions();
            static bool isBuiltinFunction(Symbol* symbol);
            static BuiltinFunction* getBuiltinFunction(Symbol* symbol);

            Environment() : enclosingEnv(nullptr) {}
            Environment(Environment* env) : enclosingEnv(env) {}

            std::string summary() {
                std::stringstream buffer;

                buffer << "{"; 

                std::map<Symbol*,Object*,SymbolComparator>::iterator iter;
                for (iter = frame.begin(); iter != frame.end(); ++iter)
                    buffer << iter->first->toString() << ": " << iter->second->toString() << ", ";
                
                buffer << "}";

                return buffer.str();
            }

            std::map<Symbol*,Object*,SymbolComparator>* lookupTable() {
                return &frame;
            }

            std::map<Symbol*,Object*,SymbolComparator>::iterator iterator() {
                return frame.begin(); 
            }

            Object* update(Symbol* key, Object* value) {
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

            Object* put(Symbol* key, Object* value) {
                frame[key] = value;

                return value;
            }

            Object* get(Symbol* key) {
                std::map<Symbol*,Object*,SymbolComparator>::iterator iter = frame.find(key);
                if (iter == frame.end()) {
                    if (enclosingEnv != nullptr)
                        return enclosingEnv->get(key);

                    throw std::out_of_range("Environment lookup failed with key: " + key->toString());
                }

                return iter->second;
            }

            Environment* getParentEnv() {
                return enclosingEnv;
            }
    };
};

#endif // __ENVIRONMENT_H__
