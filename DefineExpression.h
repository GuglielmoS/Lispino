#ifndef __DEFINE_EXPRESSION_H__
#define __DEFINE_EXPRESSION_H__

// c++
#include <string>
#include <vector>

// lisp objects
#include "LObject.h"
#include "LCons.h"
#include "LSymbol.h"

class DefineExpression : public LObject {
    
    string *name;
    LObject *body;

public:

    DefineExpression(string& name,LObject *body) :
        name(new string(name)), body(body) {}

    LType getType() const {
        return DEFINE_EXPRESSION;
    }

    std::string prettyString() const {
        return "#<DEFINE-EXPRESSION>";
    }
    
    LObject* clone() const {
        return const_cast<DefineExpression*>(this);
    }

    LObject* eval(Environment& env) throw (EvalException);
    ~DefineExpression();

};

#endif // __DEFINE_EXPRESSION_H__
