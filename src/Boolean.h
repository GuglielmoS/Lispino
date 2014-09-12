#ifndef LISPINO_BOOLEAN_H_
#define LISPINO_BOOLEAN_H_

#include "Object.h"

namespace Lispino {

    class Boolean : public Object {
        public:

            Boolean();
            Boolean(bool value);
            
            Object* eval(Environment& env);

            void setValue(bool value);
            bool getValue() const;
            
            int compare(Object* obj);
            int compareBoolean(Boolean* obj);
            
            bool isTrue() const;
            bool isFalse() const;
            bool isBoolean() const;
            
            std::string toString() const;

        private:

            bool value;
    };
};

#endif // LISPINO_BOOLEAN_H_
