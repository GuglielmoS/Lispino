#include "IfExpr.h"

#include "Boolean.h"

namespace Lispino {
    IfExpr::IfExpr() : condition(nullptr), consequent(nullptr), alternative(nullptr) {
        /* DO NOTHING */
    }

    Object* IfExpr::eval(Environment& env) {
        Object *conditionResult = condition->eval(env);

        if (!conditionResult->isBoolean())
            throw std::runtime_error("IF: the condition must be a BOOLEAN!");
        
        if (static_cast<Boolean*>(conditionResult)->isTrue())
            return consequent->eval(env);
        else
            return alternative->eval(env);
    }

    void IfExpr::setCondition(Object* condition) {
        this->condition = condition;
    }

    void IfExpr::setConsequent(Object* consequent) {
        this->consequent = consequent;
    }

    void IfExpr::setAlternative(Object* alternative) {
        this->alternative = alternative;
    }

    Object* IfExpr::getCondition() {
        return condition;
    }

    Object* IfExpr::getConsequent() {
        return consequent;
    }

    Object* IfExpr::getAlternative() {
        return alternative;
    }

    void IfExpr::mark() {
        Object::mark();
        condition->mark();
        consequent->mark();
        alternative->mark();
    }

    bool IfExpr::isIfExpr() const {
        return true;
    }

    std::string IfExpr::toString() const {
        return "IF";
    }
}
