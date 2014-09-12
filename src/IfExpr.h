#ifndef LISPINO_IFEXPR_H_
#define LISPINO_IFEXPR_H_

#include "Object.h"

namespace Lispino {

    class IfExpr : public Object {
    
        Object *condition;
        Object *consequent;
        Object *alternative;

        public:

            IfExpr();
    
            Object* eval(Environment& env);

            void setCondition(Object* condition);
            void setConsequent(Object* consequent);
            void setAlternative(Object* alternative);

            Object* getCondition();
            Object* getConsequent();
            Object* getAlternative();

            void mark();

            bool isIfExpr() const;

            std::string toString() const;
    };
};

#endif // LISPINO_IFEXPR_H_
