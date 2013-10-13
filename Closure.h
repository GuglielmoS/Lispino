#ifndef __CLOSURE_H__
#define __CLOSURE_H__

// lisp objects
#include "LObject.h"

// for using 'extendsWith'
#include "Environment.h"

// for the declaring the body type
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

    std::string prettyString() const {
        return "#<CLOSURE>"; 
    }

    Environment* getEnv() { 
        return closureEnv;
    }

    LambdaExpression* getBody() {
        return body;
    }
    
    LObject* eval(Environment& env) throw (EvalException);
    ~Closure();

};

#endif // __CLOSURE_H__
