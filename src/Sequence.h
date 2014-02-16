#ifndef __SEQUENCE_H__
#define __SEQUENCE_H__

#include "Object.h"

#include <vector>

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

#endif // __SEQUENCE_H__
