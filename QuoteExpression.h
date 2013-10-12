#ifndef __QUOTE_EXPRESION_H__
#define __QUOTE_EXPRESION_H__

#include "LObject.h"
#include "LNilObject.h"

class QuoteExpression : public LObject {

    LObject* expression;

public:

    QuoteExpression(LObject *expr) : expression(expr) {}

    LType getType() const {
        return QUOTE_EXPRESSION;
    }

    std::string prettyString() const {
        return expression->prettyString();
    }

    LObject* clone() const {
        return const_cast<QuoteExpression*>(this);
    }

    LObject* eval(Environment& env) throw (EvalException);
    ~QuoteExpression();
};

#endif // __QUOTE_EXPRESION_H__

