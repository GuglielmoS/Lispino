#include "DefineExpression.h"

LObject* DefineExpression::eval(Environment& env) throw (EvalException) {
    if (body->isLambda() or body->isClosure())
        return env.bind(*name, body);
    else
        return env.bind(*name, body->eval(env));
}

DefineExpression::~DefineExpression() {
    delete name;
    delete body;
}
