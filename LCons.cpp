#include "LCons.h"

LObject* LCons::tryLambdaCall(LambdaExpression *lambda, LObject *argsVal, Environment& env)
    throw (EvalException) {
    
    Environment tempEnv;
    std::vector<LSymbol*> *argsNames = lambda->getArgumentsNames();

    if (argsVal == 0 and argsNames == 0)
        return lambda->eval(env, tempEnv);
    else if (argsVal != 0 and not argsVal->isCons())
        throw InvalidFunctionCallException();

    // extend the new environment with the arguments
    int currentArg = 0;
    if (argsNames->size() > 0) {
        LObject *temp = next;
        while (temp->isCons() && currentArg < argsNames->size()) {
            std::string curArg = argsNames->at(currentArg)->getValue();
            tempEnv.bind(curArg, car(dynamic_cast<LCons*>(temp))->eval(env)); 
            temp = cdr(dynamic_cast<LCons*>(temp));
            currentArg++;
        }

        if (not temp->isNIL())
            throw InvalidFunctionCallException();
    }

    /*
    cout << "LAMBDA ARGS: ";
    for (int i = 0; i < argsNames->size(); i++) cout << argsNames->at(i) << " ";
    cout << endl

    cout << "AD-HOC ENV DUMP:" << endl;
    std::map<std::string, LObject*> *symbolsTable = tempEnv.getSymbolsTable();
    for(map<string, LObject*>::iterator it = symbolsTable->begin(); 
        it != symbolsTable->end(); ++it) 
      cout << "\t" << it->first << " = " << it->second << endl;
    */
  
    if (currentArg == argsNames->size())
        return lambda->eval(env, tempEnv);

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
            }
        }
        else if (first->isLambda()) {
            return tryLambdaCall(dynamic_cast<LambdaExpression*>(first), next, env);
        }
        else if (first->isCons()) {
            return tryLambdaCall(dynamic_cast<LambdaExpression*>(first->eval(env)), next, env);
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

string LCons::prettyString() const {
    return prettyStringHelper();
}

LCons::~LCons() {
    if (first != 0)
        delete first;
    if (next != 0)
        delete next;
}

