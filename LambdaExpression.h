#ifndef __LAMBDA_H__
#define __LAMBDA_H__

#include <string>
#include <vector>

#include "LObject.h"
#include "LCons.h"
#include "LSymbol.h"

class LambdaExpression : public LObject {

    LObject *body;
    std::vector<LSymbol*> *args;

public:

    LambdaExpression(std::vector<LSymbol*> *args, LObject *body) : args(args), body(body) {}

    LType getType() const {
        return LAMBDA_EXPRESSION;
    }

    std::string prettyString() const {
        return "#LAMBDA";
    }
    
    LObject* clone() const {
        return const_cast<LambdaExpression*>(this);
    }

    std::vector<LSymbol*>* getArgumentsNames() {
        return args;
    }

    LObject* eval(Environment& env) throw (EvalException);
    LObject* eval(Environment& mainEnv, Environment &argsEnv) throw (EvalException); 
    ~LambdaExpression();

};

#endif // __LAMBDA_H__
