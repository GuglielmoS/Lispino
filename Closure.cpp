#include "Closure.h"

#include "LambdaExpression.h"

LObject* Closure::eval(Environment& env) throw (EvalException) {
    Environment *finalEnv = closureEnv->extendsWith(env);
    LObject *result = body->eval(*finalEnv);
    delete finalEnv;

    return result;
}

Closure::~Closure() {
    delete body;
    delete closureEnv;   
}
