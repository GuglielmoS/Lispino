#ifndef LISPINO_SEQUENCE_H_
#define LISPINO_SEQUENCE_H_

#include <vector>

#include "Object.h"

namespace Lispino {
    
    class Sequence : public Object {
    
        std::vector<Object*> expressions;

        public:
            
            Sequence() { /* DO NOTHING */ }

            Object* eval(Environment& env);

            void setValue(std::vector<Object*> value);
            std::vector<Object*>& getValue();

            void mark();

            bool isSequence() const;

            std::string toString() const;
    };
};

#endif // LISPINO_SEQUENCE_H_
