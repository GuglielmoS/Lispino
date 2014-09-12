#ifndef LISPINO_SEQUENCE_H_
#define LISPINO_SEQUENCE_H_

#include <vector>

#include "Object.h"

namespace Lispino {
    
    class Sequence : public Object {
        public:

            void setValue(std::vector<Object*> value);
            std::vector<Object*>& getValue();

            Object* eval(Environment& env);

            void mark();

            bool isSequence() const;

            std::string toString() const;

        private:

            std::vector<Object*> expressions;
    };
};

#endif // LISPINO_SEQUENCE_H_
