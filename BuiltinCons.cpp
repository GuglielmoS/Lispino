#include "BuiltinCons.h"

// lisp objects
#include "LCons.h"

// exceptions
#include "InvalidArgumentTypeException.h"

LObject* BuiltinCons::eval(LObject* args, Environment& env) const throw (EvalException) {

    if (args == 0)
        throw InvalidArgumentTypeException();

    if (not args->isCons())
        throw InvalidArgumentTypeException();

    LObject *first = car(dynamic_cast<LCons*>(args))->eval(env);
    
    LObject *rest = cdr(dynamic_cast<LCons*>(args));
    if (not rest->isCons())
        throw InvalidArgumentTypeException();

    LObject *second = car(dynamic_cast<LCons*>(rest))->eval(env);

    if (second->isNIL())
        return new LCons(first);
    else
        return new LCons(first, second);
}
