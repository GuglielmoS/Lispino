#ifndef LISPINO_DEFINE_H_
#define LISPINO_DEFINE_H_

#include <string>

#include "Object.h"
#include "Symbol.h"

namespace Lispino {
    
    class Environment;

    class Define : public Object {
        public:
            
            Define(); 
            Define(Symbol *name, Object* value);

            Object* eval(Environment& env);

            void setName(Symbol *name);
            void setValue(Object *value);

            std::string getName() const;
            Object* getValue();

            void mark();
            
            bool isDefine() const;

            std::string toString() const;

        private:

            Symbol *name;
            Object *value;
    };
};

#endif // LISPINO_DEFINE_H_
