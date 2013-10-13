#include "BuiltinEqual.h"

#include "LCons.h"
#include "LDouble.h"
#include "LInteger.h"

#include "InvalidArgumentTypeException.h"

LObject* BuiltinEqual::eval(LObject* args, Environment& env) const throw (EvalException) {
    LObject *firstObj;
    bool isFirst = true;

    if (args == 0)
        throw InvalidArgumentTypeException();
    
    while (args->isCons()) {
        LObject *current = car(dynamic_cast<LCons*>(args))->eval(env);
    
        if (isFirst) {
            isFirst = false;
            firstObj = current;
        }
        else {
            if (not current->equals(firstObj))
                return LNilObject::getNIL();
        }

        args = cdr(dynamic_cast<LCons*>(args));
    }

    return new LSymbol("true");
}
