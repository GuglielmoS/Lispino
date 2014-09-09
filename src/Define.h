#ifndef __DEFINE_H__
#define __DEFINE_H__

#include "Object.h"
#include "Symbol.h"

namespace Lispino {
    
    class Define : public Object {
    
        Symbol *name;
        Object *value;

        public:
            
            Define() : name(nullptr), value(nullptr) {}
            Define(Symbol *name, Object* value) : name(name), value(value) {}

            Object* eval(Environment& env) {
                return env.put(name, value->isLambda() ? value : value->eval(env));
            }

            void setName(Symbol *name) {
                this->name = name;
            }

            void setValue(Object *value) {
                this->value = value;
            }

            std::string getName() const {
                return name->getValue();
            }

            Object* getValue() {
                return value;
            }

            void mark() {
                Object::mark();
                name->mark();
                value->mark();
            }

            bool isDefine() const {
                return true;
            }

            std::string toString() const {
                return "DEFINE";
            }
    };
};

#endif // __DEFINE_H__
