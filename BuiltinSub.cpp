#include "BuiltinSub.h"

#include "LCons.h"
#include "LDouble.h"
#include "LInteger.h"

#include "InvalidArgumentTypeException.h"

LObject* BuiltinSub::eval(LObject* args, Environment& env) const throw (EvalException) {
    double result = 0.0;
    bool isFirst = true;
    bool areAllInteger = true;

    if (args == 0)
        throw InvalidArgumentTypeException();

    while (args->isCons()) {
        LObject *current = car(dynamic_cast<LCons*>(args))->eval(env);
        
        if (current->isInteger()) {
            if (isFirst) {
                isFirst = false;
                result = dynamic_cast<LInteger*>(current)->getValue();
            }
            else
                result -= dynamic_cast<LInteger*>(current)->getValue();
        }
        else {
            if (current->isDouble()) {
                areAllInteger = false;

                if (isFirst) {
                    isFirst = false;
                    result = dynamic_cast<LDouble*>(current)->getValue();
                }
                else
                    result -= dynamic_cast<LDouble*>(current)->getValue();
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
