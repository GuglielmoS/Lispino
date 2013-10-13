#ifndef __LCONS_H__
#define __LCONS_H__

// c++
#include <sstream>
#include <string>

// for the evaluation
#include "Environment.h"

// lisp objects
#include "LObject.h"
#include "LNilObject.h"
#include "LSymbol.h"

// exceptions
#include "EvalException.h"
#include "InvalidFunctionCallException.h"
#include "UndefinedBuiltinFunctionException.h"

using namespace std;

class Closure;
class LambdaExpression;

class LCons : public LObject {
    
    LObject *first;
    LObject *next;
    
    LObject* tryClosureCall(Closure *closure, LObject *argsVal, Environment& env) throw (EvalException);
    LObject* tryLambdaCall(LambdaExpression *lambda, LObject *argsVal, Environment& env) throw (EvalException);
public:
    
    LCons() : first(0), next(0) {}
    LCons(LObject* first) : first(first), next(0) {}
    LCons(LObject* first, LObject* second) :
        first(first), next(second) {}
    
    void setCar(LObject* obj) { first = obj; }
    void setCdr(LObject* obj) { next = obj; }
    bool isEmpty() const { return first == 0; }
    LType getType() const { return CONS; }

    bool isNIL() const {
        return isEmpty();
    }

    bool equals(const LObject* otherObj) const;

    LObject* eval(Environment& env) throw (EvalException);

    std::string prettyStringHelper(bool parentheses = true) const;
    std::string prettyString() const;
    
    friend LObject* car(const LCons *obj) {
        return (obj != 0 && obj->first != 0) ? obj->first : LNilObject::getNIL();
    }

    friend LObject* cdr(const LCons *obj) {
        return (obj != 0 && obj->next != 0) ? obj->next : LNilObject::getNIL();
    }

    ~LCons();
};

#endif // __LCONS_H__
