#ifndef __IF_EXPRESSION_H__
#define __IF_EXPRESSION_H__

#include "Object.h"
#include "Boolean.h"

namespace Lispino {

    class IfExpr : public Object {
    
        Object *condition;
        Object *consequent;
        Object *alternative;

        public:

            IfExpr() : condition(nullptr), consequent(nullptr), alternative(nullptr) {}
    
            Object* eval(Environment& env) {
                Object *conditionResult = condition->eval(env);

                if (!conditionResult->isBoolean())
                    throw std::runtime_error("IF: the condition must be a BOOLEAN!");
                
                if (static_cast<Boolean*>(conditionResult)->isTrue())
                    return consequent->eval(env);
                else
                    return alternative->eval(env);
            }

            bool equals(Object *obj) const {
                if (this == obj)
                    return true;
                else if (obj->isIfExpr()) {
                    return static_cast<IfExpr*>(obj)->condition->equals(condition) &&
                           static_cast<IfExpr*>(obj)->consequent->equals(consequent) &&
                           static_cast<IfExpr*>(obj)->alternative->equals(alternative);
                } else
                    return false;
            }

            void setCondition(Object* condition) {
                this->condition = condition;
            }

            void setConsequent(Object* consequent) {
                this->consequent = consequent;
            }

            void setAlternative(Object* alternative) {
                this->alternative = alternative;
            }

            Object* getCondition() {
                return condition;
            }

            Object* getConsequent() {
                return consequent;
            }

            Object* getAlternative() {
                return alternative;
            }

            void mark() {
                Object::mark();
                condition->mark();
                consequent->mark();
                alternative->mark();
            }

            bool isIfExpr() const {
                return true;
            }

            std::string toString() const {
                return "IF";
            }

    };
};

#endif // __IF_EXPRESSIONS_H__
