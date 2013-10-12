#include "Parser.h"

vector<LSymbol*>* Parser::extractArgs(LCons *list) {
    // allocate a vector with the formal arguments
    vector<LSymbol*> *args = new vector<LSymbol*>();
    LObject *temp = list;

    if (temp->isCons() && not car(dynamic_cast<LCons*>(temp))->isNIL()) {
        while (temp->isCons()) {
            LObject *cur = car(dynamic_cast<LCons*>(temp));

            if (not cur->isSymbol())
                throw MalformedLambdaException();

            args->push_back(dynamic_cast<LSymbol*>(cur));
            temp = cdr(dynamic_cast<LCons*>(temp));
        }
    }

    return args;
}

LObject* Parser::parseExpr(vector<string>& tokens) throw (ParserException, TokenizerException) {
    if (tokens.size() > 0) {
        // gets the first token
        string curToken = tokens.front();
        
        // delets the first token
        tokens.erase(tokens.begin());

        // analyzes the rest of the tokens
        if (curToken[0] == '(')
            return parseList(tokens);
        else if (curToken[0] == ')')
            throw UnmatchedCloseParenthesisException();
        else if (curToken[0] == '\'')
            return new QuoteExpression(parseExpr(tokens));
        else
            return parseAtom(curToken);
    }
    else {
        throw EmptyExpressionException();
    }
}

LObject* Parser::parseList(vector<string>& tokens) throw (ParserException, TokenizerException) {
    LCons* startPtr = new LCons();
    LCons* curCons = startPtr;
    bool setCar = true,
         improperList = false,
         finalParenFound = false;

    // loops until it finds the list terminator character ')'
    while (tokens.size() > 0) {
        
        // if we are at the end of the list
        if (tokens[0] == ")") {
            finalParenFound = true;
            break;
        }
        else if (tokens[0] == "if") {
            tokens.erase(tokens.begin());
            LObject* ifExpr = parseIfExpression(tokens);
            
            if (tokens.size() == 0 || tokens[0] != ")") {
                delete ifExpr;
                throw UnbalancedParenthesesException();
            }
            else
                tokens.erase(tokens.begin());
            
            return ifExpr;
        }
        else if (tokens[0] == "quote") {
            tokens.erase(tokens.begin());

            LObject* quotedExpr = parseExpr(tokens);
            
            if (tokens.size() == 0) {
                delete quotedExpr;
                throw UnbalancedParenthesesException();
            }
            else if (tokens[0] != ")") {
                delete quotedExpr;
                throw MalformedQuoteException();
            }
            else
                tokens.erase(tokens.begin());
            
            return new QuoteExpression(quotedExpr);
        }
        else if (tokens[0] == "lambda") {
            tokens.erase(tokens.begin());
            return parseLambdaExpression(tokens);
        }
        else if (tokens[0] == "def") {
            tokens.erase(tokens.begin());

            LObject *defineExpr = parseDefineExpression(tokens);

            if (tokens.size() == 0 || tokens[0] != ")") {
                delete defineExpr;
                throw UnbalancedParenthesesException();
            }
            else
                tokens.erase(tokens.begin());

            return defineExpr;
        }        
        else if (tokens[0] == ".") {
            tokens.erase(tokens.begin());
            improperList = true;
        }

        // parses the next expression
        LObject* parsedObject = parseExpr(tokens);
        
        // sets the result in the correct position
        if (setCar) {
            curCons->setCar(parsedObject);
            setCar = false;
        }
        else {
            if (improperList) {
                curCons->setCdr(parsedObject);
                improperList = false;
            }
            else {
                LCons* newCons = new LCons(parsedObject);
                curCons->setCdr(newCons);
                curCons = newCons;
            }
        }
    }

    if (not finalParenFound) {
        delete startPtr;
        throw UnbalancedParenthesesException();
    }
    else
        tokens.erase(tokens.begin());

    return startPtr; 
}

LObject* Parser::parseDefineExpression(vector<string>& tokens) throw (ParserException, TokenizerException) {
    LObject *header = parseExpr(tokens);

    // if is a cons, it must be a function definition
    if (header->isCons()) {
        LObject *first = car(dynamic_cast<LCons*>(header));
        LObject *args = cdr(dynamic_cast<LCons*>(header));

        if (not first->isSymbol())
            throw MalformedDefineException();

        string symbolName = dynamic_cast<LSymbol*>(first)->getValue();

        if (not args->isCons() && not args->isNIL())
            throw MalformedDefineException();

        if (args->isNIL()) {
            vector<LSymbol*> *temp = new vector<LSymbol*>();
            return new DefineExpression(symbolName,
                                        new LambdaExpression(temp, parseExpr(tokens)));
        }
        else {
            LCons *argsCons = dynamic_cast<LCons*>(args);
            return new DefineExpression(symbolName,
                                        new LambdaExpression(extractArgs(argsCons), parseExpr(tokens)));
        }
    }
    // otherwise it can only be a variable definition
    else if (header->isSymbol()) {
        string symbolName = dynamic_cast<LSymbol*>(header)->getValue();
        return new DefineExpression(symbolName, parseExpr(tokens));
    }
    // the define can't be parsed because it's malformed
    else {
        throw MalformedDefineException();
    }
}

LObject* Parser::parseIfExpression(vector<string>& tokens) throw (ParserException, TokenizerException) {
    LObject *predicate = parseExpr(tokens);
    LObject *subsequentBody = 0, *alternativeBody = 0;

    if (tokens.size() > 0) {
        subsequentBody = parseExpr(tokens);
    
        if (tokens.size() > 0)
            alternativeBody = parseExpr(tokens);

        return new IfExpression(predicate, subsequentBody, alternativeBody);
    }

    throw MalformedIfException();
}

LObject* Parser::parseLambdaExpression(vector<string>& tokens) throw (ParserException, TokenizerException) {
    LObject *lambdaList = parseList(tokens);

    if (not lambdaList->isCons())
        throw MalformedLambdaException();
    
    LObject *body = cdr(dynamic_cast<LCons*>(lambdaList));

    if (not body->isCons())
        throw MalformedLambdaException();

    body = car(dynamic_cast<LCons*>(body));

    LObject *temp = car(dynamic_cast<LCons*>(lambdaList));
    if (not temp->isCons())
        throw MalformedLambdaException();

    return new LambdaExpression(extractArgs(dynamic_cast<LCons*>(temp)), body);
}

LObject* Parser::parseAtom(string& token) throw (ParserException, TokenizerException) {
    if (token[0] == '\"') {
        return new LString(token.substr(1, token.length()-2));
    }
    else if (token[0] >= '0' && token[0] <= '9') {
        if (string::npos != token.find('.'))
            return new LDouble(parseDouble(token));
        else
            return new LInteger(parseInteger(token));
    }
    else {
        if (token == "nil" || token == "NIL") {
            return LNilObject::getNIL();
        } else {
            return new LSymbol(token);
        }
    }
}

int Parser::parseInteger(string& token) throw (ParserException) {
    return atoi(token.c_str());
}

double Parser::parseDouble(string& token) throw (ParserException) {
    return atof(token.c_str());
}

LObject* Parser::parse(string& input) throw (ParserException, TokenizerException) {
    vector<string> tokens;

    Tokenizer::tokenize(input, tokens);

    if (tokens.size() == 0)
        throw EmptyExpressionException();
    
    LObject *expr = parseExpr(tokens);

    if (tokens.size() > 0) {
        delete expr;
        throw InvalidEndOfExpressionException();
    }

    return expr;
}
