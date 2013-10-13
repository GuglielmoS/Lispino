#include "LCons.h"

#include "Closure.h"
#include "LambdaExpression.h"

LObject* LCons::tryClosureCall(Closure *closure, LObject *argsVal, Environment& env)
    throw (EvalException) {

    Environment *finalEnv = closure->getEnv()->extendsWith(env);
    LObject *result = tryLambdaCall(closure->getBody(), argsVal, *finalEnv);
    delete finalEnv;

    return result;
}

LObject* LCons::tryLambdaCall(LambdaExpression *lambda, LObject *argsVal, Environment& env)
    throw (EvalException) {
    
    std::vector<LSymbol*> *argsNames = lambda->getArgumentsNames();

    if (argsVal == 0 and argsNames == 0)
        return lambda->eval(env);
    else if (argsVal != 0 and not argsVal->isCons())
        throw InvalidFunctionCallException();

    // build a new environment with the arguments related to their specific lambda name
    Environment tempEnv;
    int currentArg = 0;

    if (argsNames->size() > 0) {
        LObject *temp = next;
        while (temp->isCons() && currentArg < argsNames->size()) {
            std::string curArg = argsNames->at(currentArg)->getValue();
            LObject* curResult = car(dynamic_cast<LCons*>(temp))->eval(env);

            tempEnv.bind(curArg, curResult);
            
            temp = cdr(dynamic_cast<LCons*>(temp));
            currentArg++;
        }

        if (not temp->isNIL())
            throw InvalidFunctionCallException();
    }

    // extend the new environment with the arguments and then eval the lambda
    if (currentArg == argsNames->size()) {
        Environment *finalEnv = tempEnv.extendsWith(env);
        LObject* lambdaResult = lambda->eval(*finalEnv);

        delete finalEnv;

        return lambdaResult;
    }

    throw InvalidFunctionCallException(); 
}

LObject* LCons::eval(Environment& env) throw (EvalException) {
    if (first != 0) {
        if (first->isSymbol()) {
            std::string curArg = dynamic_cast<LSymbol*>(first)->getValue();

            // try builtin functions first
            try {
                return env.lookupBuiltinFunction(curArg)->eval(next, env);
            } catch (UndefinedBuiltinFunctionException& e) {
                // since no builtin function exists, it tries to find a lambda to execute in 
                // the overlying environment
                LObject* envVal = env.lookup(curArg);

                if (envVal->isLambda())
                    return tryLambdaCall(dynamic_cast<LambdaExpression*>(envVal), next, env); 
                else if (envVal->isClosure()) {
                    return tryClosureCall(dynamic_cast<Closure*>(envVal), next, env);
                }
            }
        }
        else if (first->isLambda()) {
            return tryLambdaCall(dynamic_cast<LambdaExpression*>(first), next, env);
        }
        else if (first->isCons()) {
            LObject *tempResult = first->eval(env);

            if (tempResult->isLambda())
                return tryLambdaCall(dynamic_cast<LambdaExpression*>(tempResult), next, env);
            else if (tempResult->isClosure())
                return tryClosureCall(dynamic_cast<Closure*>(tempResult), next, env);
        }
    }

    throw InvalidFunctionCallException();
}

string LCons::prettyStringHelper(bool parentheses) const {
    if (first == 0) {
        return LNilObject::getNIL()->prettyString();
    }
    else {
        stringstream buf;
        
        if (parentheses)
            buf << "(";
        
        buf << first->prettyString();
        
        if (next != 0) {
            if (next->isCons()) {
                buf << " ";
                buf << dynamic_cast<LCons*>(next)->prettyStringHelper(false);
            }
            else {
                buf << " . ";
                buf << next->prettyString();
            }
        }
        
        if (parentheses)
            buf << ")";

        return buf.str();
    }
}

bool LCons::equals(const LObject* otherObj) const {
    if (getType() != otherObj->getType())
        return false;

    const LCons* otherCons = dynamic_cast<const LCons*>(otherObj);

    if (not first->equals(otherCons->first))
        return false;

    if (not next->equals(otherCons->next))
        return false;

    return true;
}


string LCons::prettyString() const {
    return prettyStringHelper();
}

LCons::~LCons() {
    if (first != 0)
        delete first;
    if (next != 0)
        delete next;
}

