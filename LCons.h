#ifndef __LCONS__
#define __LCONS__

#include <sstream>
#include <string>

#include "Environment.h"

#include "LObject.h"
#include "LNilObject.h"
#include "LSymbol.h"
#include "LambdaExpression.h"

#include "EvalException.h"
#include "InvalidFunctionCallException.h"
#include "UndefinedBuiltinFunctionException.h"

using namespace std;

class LambdaExpression;

class LCons : public LObject {
    
    LObject *first;
    LObject *next;
    
public:
    
    LCons() : first(0), next(0) {}
    LCons(LObject* first) : first(first), next(0) {}
    LCons(LObject* first, LObject* second) :
        first(first), next(second) {}
    
    void setCar(LObject* obj) {
        first = obj;
    }

    void setCdr(LObject* obj) {
        next = obj;
    }

    bool isEmpty() const {
        return first == 0;
    }

    LType getType() const {
        return CONS;
    }

    LObject* tryLambdaCall(LambdaExpression *lambda, LObject *argsVal, Environment& env) throw (EvalException);
    LObject* eval(Environment& env) throw (EvalException);

    std::string prettyStringHelper(bool parentheses = true) const;
    std::string prettyString() const;
    ~LCons();
    
    friend LObject* car(const LCons *obj) {
        return (obj != 0 && obj->first != 0) ? obj->first : LNilObject::getNIL();
    }

    friend LObject* cdr(const LCons *obj) {
        return (obj != 0 && obj->next != 0) ? obj->next : LNilObject::getNIL();
    }

};

#endif // __LCONS__
