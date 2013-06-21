#include "Parser.h"

LObject* Parser::parseExpr(vector<string>& tokens) throw (ParserException) {
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
        else
            return parseAtom(curToken);
    }
    else {
        throw EmptyExpressionException();
    }
}

LCons* Parser::parseList(vector<string>& tokens) throw (ParserException) {
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

        // if it's an improper list
        if (tokens[0] == ".") {
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

LAtom* Parser::parseAtom(string& token) throw (ParserException) {
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
        return new LSymbol(token);
    }
}

int Parser::parseInteger(string& token) throw (ParserException) {
    return atoi(token.c_str());
}

double Parser::parseDouble(string& token) throw (ParserException) {
    return atof(token.c_str());
}

LObject* Parser::parse(string& input) throw (ParserException) {
    vector<string> tokens;

    Lexer::tokenize(input, tokens);

    if (tokens.size() == 0)
        throw EmptyExpressionException();
    
    return parseExpr(tokens);
}
