#ifndef __LAMBDA_H__
#define __LAMBDA_H__

// c++
#include <string>
#include <vector>

// lisp objects
#include "LObject.h"
#include "LCons.h"
#include "LSymbol.h"
#include "Closure.h"

class LambdaExpression : public LObject {

    LObject *body;
    std::vector<LSymbol*> *args;

public:

    LambdaExpression(std::vector<LSymbol*> *args, LObject *body) : 
        args(args), body(body) {}

    LType getType() const {
        return LAMBDA_EXPRESSION;
    }

    std::string prettyString() const {
        return "#<LAMBDA>";
    }
    
    std::vector<LSymbol*>* getArgumentsNames() {
        return args;
    }

    LObject* eval(Environment& env) throw (EvalException);
    LObject* eval(Environment& mainEnv, Environment &argsEnv) throw (EvalException); 
    ~LambdaExpression();

};

#endif // __LAMBDA_H__
