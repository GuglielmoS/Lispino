#include "DefineExpression.h"

LObject* DefineExpression::eval(Environment& env) throw (EvalException) {
    return env.bind(*name, body);
}

DefineExpression::~DefineExpression() {
    delete name;
    delete body;
}
