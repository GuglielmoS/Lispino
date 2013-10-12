#include "QuoteExpression.h"

LObject* QuoteExpression::eval(Environment& env) throw (EvalException) {
    return expression;
}

QuoteExpression::~QuoteExpression() {
    delete expression;
}

