#include "BuiltinSum.h"

#include "LCons.h"
#include "LDouble.h"
#include "LInteger.h"

#include "InvalidArgumentTypeException.h"

LObject* BuiltinSum::eval(LObject* args, Environment& env) const throw (EvalException) {
    double result = 0.0;
    bool areAllInteger = true;

    if (args == 0)
        throw InvalidArgumentTypeException();

    while (args->isCons()) {
        LObject *current = car(dynamic_cast<LCons*>(args))->eval(env);
        
        if (current->isInteger()) {
            result += dynamic_cast<LInteger*>(current)->getValue();
        }
        else {
            if (current->isDouble()) {
                result += dynamic_cast<LDouble*>(current)->getValue();
                areAllInteger = false;
            }
            else
                throw InvalidArgumentTypeException();
        }

        args = cdr(dynamic_cast<LCons*>(args));
    }

    if (areAllInteger)
        return new LInteger(static_cast<long int>(result));
    else
        return new LDouble(result);
}
