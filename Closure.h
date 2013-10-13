#ifndef __CLOSURE_H__
#define __CLOSURE_H__

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "LObject.h"
#include "Environment.h"

class LambdaExpression;

class Closure : public LObject {

    LambdaExpression *body;
    Environment *closureEnv;

public:

    Closure(LambdaExpression *body, Environment& env) : body(body) {
        Environment temp;
        closureEnv = temp.extendsWith(env);
    }

    LType getType() const {
        return CLOSURE;
    }

    Environment* getEnv() {
        return closureEnv;
    }

    LambdaExpression* getBody() {
        return body;
    }

    std::string prettyString() const {
        return "#<CLOSURE>";
    }
    
    LObject* eval(Environment& env) throw (EvalException);
    ~Closure();

};

#endif // __CLOSURE_H__
