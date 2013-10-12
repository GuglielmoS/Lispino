#include "DefineExpression.h"

LObject* DefineExpression::eval(Environment& env) throw (EvalException) {
    return env.bind(*name, body->eval(env));
}

DefineExpression::~DefineExpression() {
    delete name;
    delete body;
}
