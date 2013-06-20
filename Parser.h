#ifndef __PARSER__

#define __PARSER__

#include <cstdlib>
#include <vector>
#include <sstream>
#include <string>

#include "Lexer.h"
#include "LObject.h"
#include "LNilObject.h"
#include "LCons.h"
#include "LAtom.h"
#include "LString.h"
#include "LInteger.h"
#include "LDouble.h"
#include "LSymbol.h"

using namespace std;

class Parser {

    static LObject* parseExpr(vector<string>& tokens) {
        string curToken = tokens.front();
        
        tokens.erase(tokens.begin());

        if (curToken[0] == '(')
            return parseList(tokens);
        else if (curToken[0] == ')')
            return LNilObject::getNIL();
        else
            return parseAtom(curToken);
    }

    static LCons* parseList(vector<string>& tokens) {
        LCons* first = new LCons();
        LCons* curCons = first;
        bool setCar = true,
             improperList = false;

        // loops until it finds the list terminator character ')'
        while (tokens[0] != ")") {

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

        // remove the ')' token
        tokens.erase(tokens.begin());

        return first; 
    }

    static LAtom* parseAtom(string& token) {
        if (token[0] == '\"') {
            return new LString(token.substr(1, token.length()-2));
        }
        else if (token[0] >= '0' && token[0] <= '9') {
            if (string::npos != token.find('.')) {
                return new LDouble(parseDouble(token));
            }
            else {
                return new LInteger(parseInteger(token));
            }
        }
        else {
            return new LSymbol(token);
        }
    }

    static int parseInteger(string& token) {
        return atoi(token.c_str());
    }

    static double parseDouble(string& token) {
        return atof(token.c_str());
    }

public:
    
    static LObject* parse(string& input) {
        vector<string> tokens;

        Lexer::tokenize(input, tokens);

        if (tokens.size() == 0)
            return LNilObject::getNIL();
        
        return parseExpr(tokens);
    }

};

#endif // __PARSER__

