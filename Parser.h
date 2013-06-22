#ifndef __PARSER__

#define __PARSER__

#include <cstdlib>
#include <vector>
#include <sstream>
#include <string>

// tokens
#include "Lexer.h"

// objects
#include "LObject.h"
#include "LNilObject.h"
#include "LCons.h"
#include "LAtom.h"
#include "LString.h"
#include "LInteger.h"
#include "LDouble.h"
#include "LSymbol.h"

// exceptions
#include "ParserException.h"
#include "EmptyExpressionException.h"
#include "UnbalancedParenthesesException.h"
#include "UnmatchedCloseParenthesisException.h"

using namespace std;

class Parser {

    /**
     * Parser for a generic expression.
     */
    static LObject* parseExpr(vector<string>& tokens) throw (ParserException); 

    /**
     * Specific parsers for each type involved in the language.
     */
    static LCons* parseList(vector<string>& tokens) throw (ParserException);
    static LAtom* parseAtom(string& token) throw (ParserException);
    static int parseInteger(string& token) throw (ParserException);
    static double parseDouble(string& token) throw (ParserException);

    /**
     * helpers
     */
    static LCons* quote(LObject *expr);

public:
    
    /**
     * Parses and returns an object which represents the expression given
     * as argument.
     */
    static LObject* parse(string& input) throw (ParserException);
};

#endif // __PARSER__

