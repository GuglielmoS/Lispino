#include "BuiltinDiv.h"

// lisp objects
#include "LCons.h"
#include "LDouble.h"
#include "LInteger.h"

// exceptions
#include "DivisionByZeroException.h"
#include "InvalidArgumentTypeException.h"

LObject* BuiltinDiv::eval(LObject* args, Environment& env) const throw (EvalException) {
    bool isFirst = true;
    bool areAllInteger = true;

    double result = 0.0;

    if (args == 0)
        throw InvalidArgumentTypeException();

    while (args->isCons()) {
        LObject *current = car(dynamic_cast<LCons*>(args))->eval(env);
        
        if (current->isInteger()) {
            if (isFirst) {
                isFirst = false;
                result = dynamic_cast<LInteger*>(current)->getValue();
            }
            else {
                int temp = dynamic_cast<LInteger*>(current)->getValue();

                if (temp != 0)
                    result /= temp;
                else
                    throw DivisionByZeroException();
            }
        }
        else {
            if (current->isDouble()) {
                areAllInteger = false;

                if (isFirst) {
                    isFirst = false;
                    result = dynamic_cast<LDouble*>(current)->getValue();
                }
                else {
                    int temp = dynamic_cast<LDouble*>(current)->getValue();

                    if (temp != 0)
                        result /= temp;
                    else
                        throw DivisionByZeroException();
                }
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
