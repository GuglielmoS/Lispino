#include "LambdaExpression.h"

LObject* LambdaExpression::eval(Environment& env) throw (EvalException) {
    if (body->isLambda())
        return new Closure(dynamic_cast<LambdaExpression*>(body), env);
    else
        return body->eval(env);
}

LambdaExpression::~LambdaExpression() {
    delete body;
    delete args;
}
