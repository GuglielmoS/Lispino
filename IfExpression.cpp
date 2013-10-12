#include "IfExpression.h"

LObject* IfExpression::eval(Environment& env) throw (EvalException) {
    if (not predicate->eval(env)->isNIL())
        return subsequentBody->eval(env);
    else {
        if (alternativeBody != 0)
            return alternativeBody->eval(env);
    }

    return LNilObject::getNIL();
}

IfExpression::~IfExpression() {
    delete predicate;
    delete subsequentBody;
    delete alternativeBody;
}
