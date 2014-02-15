#ifndef __QUOTE_H__
#define __QUOTE_H__

#include "Object.h"

namespace Lispino {

    class Quote : public Object {
        
        Object *value;

        public:

            Quote() : value(nullptr) {}
            Quote(Object* value) : value(value) {}
    
            Object* eval(Environment& env) {
                return value;
            }

            void setValue(Object* value) {
                this->value = value;
            }
        
            Object* getValue() {
                return value;
            }

            void mark() {
                Object::mark();
                value->mark();
            }

            bool isQuote() const {
                return true;
            }

            std::string toString() const {
                return "'" + value->toString();
            }

    };
};

#endif // _QUOTE_H__
