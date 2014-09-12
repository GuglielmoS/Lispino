#ifndef LISPINO_QUOTE_H_
#define LISPINO_QUOTE_H_

#include "Object.h"

namespace Lispino {

    class Environment;

    class Quote : public Object {
        
        Object *value;

        public:

            Quote();
            Quote(Object* value);
    
            Object* eval(Environment& env);

            void setValue(Object* value);
            Object* getValue();

            void mark();

            bool isQuote() const;

            std::string toString() const;
    };
};

#endif // LISPINO_QUOTE_H_
