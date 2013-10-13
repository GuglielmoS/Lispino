#include "BuiltinCar.h"

#include "LCons.h"

#include "InvalidArgumentTypeException.h"

LObject* BuiltinCar::eval(LObject* args, Environment& env) const throw (EvalException) {

    if (args == 0)
        throw InvalidArgumentTypeException();

    if (not args->isCons())
        throw InvalidArgumentTypeException();

    LObject *arg = car(dynamic_cast<LCons*>(args))->eval(env);

    if (not arg->isCons())
        throw InvalidArgumentTypeException();

    return car(dynamic_cast<LCons*>(arg));
}
