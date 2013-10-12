#include "LambdaExpression.h"

LObject* LambdaExpression::eval(Environment& env) throw (EvalException) {
    return this;
}

LObject* LambdaExpression::eval(Environment& mainEnv, Environment &argsEnv)
    throw (EvalException) {
    
    Environment *finalEnv = mainEnv.extendsWith(argsEnv);
    LObject *result = body->eval(*finalEnv);
    delete finalEnv;

    return result;
}

LambdaExpression::~LambdaExpression() {
    delete body;
    delete args;
}
