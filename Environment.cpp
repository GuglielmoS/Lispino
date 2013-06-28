#include "Environment.h"

Environment::Environment() : parent(0) { addBuiltinFunctions(); }

Environment::Environment(Environment *parent) : parent(parent) {}

void Environment::addBuiltinFunctions() {
    builtinFunctions.push_back(new BuiltinSum("+"));
    builtinFunctions.push_back(new BuiltinProduct("*"));
    builtinFunctions.push_back(new BuiltinDecrement("dec"));
    builtinFunctions.push_back(new BuiltinCar("car"));
    builtinFunctions.push_back(new BuiltinCdr("cdr"));
}

BuiltinFunction* Environment::findBuiltinFunc(const string& funcName) const 
    throw (EnvironmentException) {

    for (unsigned int i = 0; i < builtinFunctions.size(); i++)
        if (builtinFunctions[i]->getName() == funcName)
            return builtinFunctions[i];

    if (parent != 0)
        return parent->findBuiltinFunc(funcName);

    throw BuiltinFunctionNotFoundException();
}

void Environment::applyEnv(vector<LObject*>& args) throw (EnvironmentException) {
    for (unsigned int i = 0; i < args.size(); i++) {
        if (args[i]->isAtom()) {
            LAtom* curAtom = dynamic_cast<LAtom*>(args[i]);

            if (curAtom->isSymbol()) {
                LObject *curValue = valueOf(dynamic_cast<LSymbol*>(curAtom)); 
                
                delete args[i];
                args[i] = curValue;
            }
        }
    }
}

void Environment::extractArguments(const LCons *operands, vector<LObject*>& args, bool withEval) 
    throw (EnvironmentException) {
    
    LCons* curOp = const_cast<LCons*>(operands);

    while (not curOp->isEmpty()) {
        args.push_back(withEval ? evalExpr(car(curOp)) : car(curOp));

        LObject* nextOp = cdr(curOp);

        if (nextOp->isCons()) {
            curOp = dynamic_cast<LCons*>(nextOp);
        }
        else {
            if (not nextOp->isNIL())
                args.push_back(withEval ? evalExpr(nextOp) : nextOp);

            break;
        }
    }
}

LObject* Environment::evalExpr(LObject *expr) throw (EnvironmentException) {
    if (expr->isAtom())
        return evalAtom(dynamic_cast<LAtom*>(expr));
    else if (expr->isCons())
        return evalCons(dynamic_cast<LCons*>(expr));
    else if (expr->isLambda())
        return expr;
    else
        return expr;
}

LObject* Environment::evalAtom(LAtom *expr) throw (EnvironmentException) {
    if (expr->isSymbol())
        return valueOf(dynamic_cast<LSymbol*>(expr));
    else
        return expr;
}

LObject* Environment::evalCons(LCons *expr) throw (EnvironmentException) {
    LCons* list = dynamic_cast<LCons*>(expr);
    LObject* firstArg = car(list);
    
    if (firstArg->isAtom()) {
        if (dynamic_cast<LAtom*>(firstArg)->isSymbol()) {
            LSymbol *funcSymbol = dynamic_cast<LSymbol*>(firstArg);
            string funcName = funcSymbol->getValue();
            LCons *operands = dynamic_cast<LCons*>(cdr(list));

            // defines function
            if (funcName == "def") {
                return define(operands, cdr(operands));
            }
            else if (funcName == "lambda") {
                if (car(operands)->isCons() and cdr(operands)->isCons()) {
                    if (car(dynamic_cast<LCons*>(cdr(operands)))->isCons())
                        return defineLambda(dynamic_cast<LCons*>(car(operands)),
                                            dynamic_cast<LCons*>(car(dynamic_cast<LCons*>(cdr(operands)))));
                }
                
                throw InvalidArgumentException();
            }
            else if (funcName == "quote") {
                return quote(operands);
            }
            else {
                return tryFunctionApplication(funcSymbol, operands);
            }
        }
    }
    else if (firstArg->isCons()) {
        LCons *consExpr = dynamic_cast<LCons*>(firstArg);

        if (cdr(list)->isCons()) {
            LCons *operands = dynamic_cast<LCons*>(cdr(list));
            LObject *result = evalCons(consExpr);

            if (result->isLambda()) {
                vector<LObject*> args;
                extractArguments(operands, args);

                return dynamic_cast<LLambda*>(result)->call(args);
            }
        }
    }

    throw InvalidFunctionCallException();
}

LObject* Environment::tryFunctionApplication(LSymbol *symbol, LCons *operands)
    throw (EnvironmentException) {

    try {
        return tryBuiltinFunction(symbol, operands);
    }
    catch (BuiltinFunctionNotFoundException& e) {
        return tryLambda(symbol, operands);
    }
}

LObject* Environment::tryLambda(LSymbol *symbol, LCons *operands) throw (EnvironmentException) {
    LObject *result = valueOf(symbol);

    if (result->isLambda()) {
        vector<LObject*> args;
        LLambda *lambda = dynamic_cast<LLambda*>(result); 

        extractArguments(operands, args);
        applyEnv(args);

        return lambda->call(args);
    }
    else
        throw InvalidFunctionException();
}

LObject* Environment::tryBuiltinFunction(LSymbol *symbol, LCons *operands) throw (EnvironmentException) {
    BuiltinFunction* builtinFunc = findBuiltinFunc(symbol->getValue());
    vector<LObject*> args;

    extractArguments(operands, args);
    applyEnv(args);

    return builtinFunc->apply(args);
}

LSymbol* Environment::defineFunction(LCons *funcArgs, LObject *body) throw (EnvironmentException) {
    if (car(funcArgs)->isAtom() and cdr(funcArgs)->isCons()) {
        LAtom *atomValue = dynamic_cast<LAtom*>(car(funcArgs));
        LCons *argValues = dynamic_cast<LCons*>(cdr(funcArgs));

        if (atomValue->isSymbol()) {
            LSymbol *funcSymbol = dynamic_cast<LSymbol*>(atomValue);
            string funcName = dynamic_cast<LSymbol*>(atomValue)->getValue();

            if (body->isCons()) {
                LObject* funcBody = car(dynamic_cast<LCons*>(body));
                
                // gets the parameters
                vector<LObject*> args;
                extractArguments(argValues, args, false);

                for (unsigned int i = 0; i < args.size(); i++) {
                    if (not args[i]->isAtom())
                        throw InvalidFunctionException();
                    else if (not dynamic_cast<LAtom*>(args[i])->isSymbol())
                        throw InvalidFunctionException();
                }

                // adds the lambda to the environment
                bind(funcSymbol, new LLambda(args, funcBody, this));
                
                return new LSymbol(funcName);
            }
        }
    }

    throw InvalidFunctionException();
}

LLambda* Environment::defineLambda(LCons *operands, LCons *body) throw (EnvironmentException) {
    vector<LObject*> args;
    extractArguments(operands, args, false);

    return new LLambda(args, body, this);
}

LSymbol* Environment::defineSymbol(LSymbol *symbol, LObject *value) throw (EnvironmentException) {
    LObject *symValue = value;

    if (value->isCons()) {
        LCons* consValue = dynamic_cast<LCons*>(value);

        if (cdr(consValue)->isNIL())
            symValue = car(consValue);
    }

    // adds the symbol to the symbols table
    bind(symbol, evalExpr(symValue));

    return new LSymbol(symbol->getValue());
}

LObject* Environment::define(LCons *args, LObject *body) throw (EnvironmentException) {
    if (car(args)->isCons())
        return defineFunction(dynamic_cast<LCons*>(car(args)), body);
    else if (car(args)->isAtom()) {
        if (dynamic_cast<LAtom*>(car(args))->isSymbol())
            return defineSymbol(dynamic_cast<LSymbol*>(car(args)), body);
    }

    throw InvalidFunctionException();
}

LObject* Environment::quote(LCons* operands) throw (EnvironmentException) {
    if (car(operands)->isAtom()) {
        LAtom* atomValue = dynamic_cast<LAtom*>(car(operands));
        
        if (atomValue->isSymbol() && cdr(operands)->isNIL())
            return atomValue;
        else
            throw InvalidQuoteException();
    }
    else if (car(operands)->isCons() && cdr(operands)->isNIL()) {
        return car(operands);
    }
    else {
        throw InvalidQuoteException();
    }
}

void Environment::setParentEnv(Environment* env) {
    parent = env;
}

void Environment::bind(LSymbol* symbol, LObject* value) {
    try { 
        LObject* oldValue = valueOf(symbol);
        delete oldValue;
    }
    catch (UndefinedSymbolException& e) { /* DO NOTHING */ }

    // update the value
    symTable[symbol->getValue()] = value;
}

LObject* Environment::valueOf(LSymbol* symbol) throw (EnvironmentException) {
    if (symbol != 0) {
        string symName = symbol->getValue();
        map<string,LObject*>::iterator it = symTable.find(symName);
        
        if (it != symTable.end()) {
            return it->second;
        }
        else {
            if (parent != 0)
                return parent->valueOf(symbol);
            else
                throw UndefinedSymbolException();
        }
    }
    else
        throw UndefinedSymbolException();
}

LObject* Environment::eval(string& inputExpr) throw (LispinoException) {
    return evalExpr(Parser::parse(inputExpr));
}

LObject* Environment::eval(LObject* expr) throw (LispinoException) {
    return evalExpr(expr);
}

Environment::~Environment() {
    builtinFunctions.clear();
    symTable.clear();
}

