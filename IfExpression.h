#ifndef __IF_EXPRESION_H__
#define __IF_EXPRESION_H__

#include "LObject.h"
#include "LNilObject.h"

class IfExpression : public LObject {

    LObject* predicate;
    LObject* subsequentBody;
    LObject* alternativeBody;

public:

    IfExpression(LObject *pred, LObject *trueCase, LObject *falseCase) :
        predicate(pred), subsequentBody(trueCase), alternativeBody(falseCase) {}

    LType getType() const {
        return IF_EXPRESSION;
    }

    std::string prettyString() const {
        return "#IF-EXPRESSION";
    }

    LObject* clone() const {
        return const_cast<IfExpression*>(this);
    }

    LObject* eval(Environment& env) throw (EvalException);
    ~IfExpression();
};

#endif // __IF_EXPRESION_H__
