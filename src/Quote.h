#ifndef LISPINO_QUOTE_H_
#define LISPINO_QUOTE_H_

#include "Object.h"

namespace Lispino {

    class Environment;

    class Quote : public Object {
        public:

            Quote();
            Quote(Object* value);
 
            void setValue(Object* value);
            Object* getValue();
   
            Object* eval(Environment& env);

            void mark();

            bool isQuote() const;

            std::string toString() const;

        private:

            Object *value;
    };
};

#endif // LISPINO_QUOTE_H_
