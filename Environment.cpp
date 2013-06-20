#include "Environment.h"

BuiltinFunction* Environment::findBuiltinFunc(const string& funcName) const {
    int pos = -1;
    for (unsigned int i = 0; i < builtinFunctions.size(); i++) {
        if (builtinFunctions[i]->getName() == funcName) {
            pos = i;
            break;
        }
    }

    return (pos == -1) ? 0 : builtinFunctions[pos];
}

void Environment::extractArguments(const LCons *operands, vector<LObject*>& args, bool withEval) {
    LCons* curOp = const_cast<LCons*>(operands);

    while (not curOp->isEmpty()) {
        if (withEval)
            args.push_back(evalExpr(car(curOp)));
        else
            args.push_back(car(curOp));

        LObject* nextOp = cdr(curOp);
        if (nextOp->isCons()) {
            curOp = dynamic_cast<LCons*>(nextOp);
        }
        else {
            if (not nextOp->isNIL()) {
                if (withEval)
                    args.push_back(evalExpr(nextOp));
                else
                    args.push_back(nextOp);
            }

            break;
        }
    }
}

LObject* Environment::evalAtom(LAtom *expr) {
    if (expr->isSymbol()) {
        string symName = dynamic_cast<LSymbol*>(expr)->getValue();

        map<string,LObject*>::iterator it = symTable.find(symName);
        if (it != symTable.end()) {
            return it->second;
        }
        else {
            cout << "UNBOUND VARIABLE: \"" << symName << "\"" << endl;
            return LNilObject::getNIL();
        }
    }
    else {
        return expr;
    }
}

LObject* Environment::evalCons(LCons *expr) {
    LCons* list = dynamic_cast<LCons*>(expr);
    LObject* firstArg = car(list);
    
    if (firstArg->isAtom()) {
        if (dynamic_cast<LAtom*>(firstArg)->isSymbol()) {
            string funcName = dynamic_cast<LSymbol*>(firstArg)->getValue();
            LCons *operands = dynamic_cast<LCons*>(cdr(list));
            
            // defines function                    
            if (funcName == "def") {
                return define(operands, cdr(operands));
            }
            else if (funcName == "quote") {
                if (car(operands)->isAtom()) {
                    LAtom* atomValue = dynamic_cast<LAtom*>(car(operands)); 
                    
                    if (atomValue->isSymbol() && cdr(operands)->isNIL()) {
                        return atomValue;
                    }
                    else {
                        cout << "ILLEGAL QUOTE!" << endl;
                        return LNilObject::getNIL();
                    }
                }
                else if (car(operands)->isCons() && cdr(operands)->isNIL()) {
                    return car(operands);
                }
                else {
                    cout << "ILLEGAL QUOTE!" << endl;
                    return LNilObject::getNIL();
                }
            }
            else {
                BuiltinFunction* builtinFunc = findBuiltinFunc(funcName);

                if (builtinFunc != 0) {
                    vector<LObject*> args;
                    extractArguments(operands, args);
                    
                    if (applyEnv(args))
                        return builtinFunc->apply(args);
                    else
                        return LNilObject::getNIL();
                }
                else {
                    map<string,LObject*>::iterator it = symTable.find(funcName);

                    // tries to apply an environment function                            
                    if (it != symTable.end()) {
                        if (it->second->isLambda()) {
                            LLambda *lambda = dynamic_cast<LLambda*>(it->second); 

                            vector<LObject*> args;
                            extractArguments(operands, args);

                            if (applyEnv(args))
                                return lambda->call(args);
                            else
                                return LNilObject::getNIL();
                        }
                    }
                    
                    cout << "UNDEFINED FUNCTION: \"" << funcName << "\"" << endl;
                    return LNilObject::getNIL();
                }
            }
        }
        else {
            return list;
        }
    }
    else {
        return list;
    }
}

LObject* Environment::evalExpr(LObject *expr) {
    if (expr->isAtom())
        return evalAtom(dynamic_cast<LAtom*>(expr));
    else if (expr->isCons())
        return evalCons(dynamic_cast<LCons*>(expr));
    else if (expr->isLambda())
        return expr;
    else
        return expr;
}


LObject* Environment::defineFunction(LCons *funcArgs, LObject *body) {
    if (car(funcArgs)->isAtom() and cdr(funcArgs)->isCons()) {
        LAtom *atomValue = dynamic_cast<LAtom*>(car(funcArgs));
        LCons *argsValue = dynamic_cast<LCons*>(cdr(funcArgs));

        if (atomValue->isSymbol()) {
            string funcName = dynamic_cast<LSymbol*>(atomValue)->getValue();

            if (body->isCons()) {
                LObject* funcBody = car(dynamic_cast<LCons*>(body));
                
                // gets the parameters
                vector<LObject*> args;
                extractArguments(argsValue, args, false);
                
                // adds the lambda to the environment
                symTable[funcName] = new LLambda(args, funcBody, this);

                return atomValue;
            }
        }
    }

    cout << "ILLEGAL DEFINE!" << endl;
    return LNilObject::getNIL();
}

LObject* Environment::defineSymbol(LSymbol *symbol, LObject *value) {
    LObject *symValue = value;

    if (value->isCons()) {
        LCons* consValue = dynamic_cast<LCons*>(value);

        if (cdr(consValue)->isNIL())
            symValue = car(consValue);
    }

    // adds the symbol to the symbols table
    symTable[symbol->getValue()] = evalExpr(symValue);

    return symbol;
}

LObject* Environment::define(LCons *args, LObject *body) {
    if (car(args)->isCons())
        return defineFunction(dynamic_cast<LCons*>(car(args)), body);
    else if (car(args)->isAtom()) {
        if (dynamic_cast<LAtom*>(car(args))->isSymbol())
            return defineSymbol(dynamic_cast<LSymbol*>(car(args)), body);
    }

    cout << "ILLEGAL DEFINE!" << endl;
    return LNilObject::getNIL();
}

void Environment::addBuiltinFunctions() {
    builtinFunctions.push_back(new BuiltinSum("+"));
    builtinFunctions.push_back(new BuiltinProduct("*"));
    builtinFunctions.push_back(new BuiltinDecrement("dec"));
}

bool Environment::applyEnv(vector<LObject*>& args) {
    for (unsigned int i = 0; i < args.size(); i++) {
        if (args[i]->isAtom()) {
            LAtom* curAtom = dynamic_cast<LAtom*>(args[i]);

            if (curAtom->isSymbol()) {
                string symName = dynamic_cast<LSymbol*>(curAtom)->getValue();
                
                map<string,LObject*>::iterator it = symTable.find(symName);
                if (it != symTable.end()) {
                    delete args[i];
                    args[i] = it->second;
                }
                else {
                    cout << "UNBOUND VARIABLE: \"" << symName << "\"" << endl;
                    return false;
                }
            }
        }
    }

    return true;
}

void Environment::bind(LSymbol* symName, LObject* value) {
    symTable[symName->getValue()] = value;
}

LObject* Environment::valueOf(LSymbol* symbol) {
    if (symbol != 0) {
        string symName = symbol->getValue();

        map<string,LObject*>::iterator it = symTable.find(symName);
        if (it != symTable.end()) {
            return it->second;
        }
        else {
            if (parent != 0)
                return parent->valueOf(symbol);
        }
    }
    else {
        return 0;
    }
    
    cout << "UNBOUND VARIABLE: \"" << symbol->getValue() << "\"" << endl;
    return LNilObject::getNIL();
}

LObject* Environment::eval(string& inputExpr) {
    return evalExpr(Parser::parse(inputExpr));
}

LObject* Environment::eval(LObject* expr) {
    return evalExpr(expr);
}

void Environment::setParentEnv(Environment* env) {
    parent = env;
}

Environment::~Environment() {
    while (builtinFunctions.size() > 0)
       builtinFunctions.pop_back(); 
}

