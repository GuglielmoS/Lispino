#ifndef __PARSER__

#define __PARSER__

#include <cstdlib>
#include <vector>
#include <sstream>
#include <string>

// tokens
#include "Tokenizer.h"

// objects
#include "LObject.h"
#include "LNilObject.h"
#include "LCons.h"
#include "LString.h"
#include "LInteger.h"
#include "LDouble.h"
#include "LSymbol.h"
#include "IfExpression.h"
#include "QuoteExpression.h"
#include "LambdaExpression.h"
#include "DefineExpression.h"

// exceptions
#include "ParserException.h"
#include "MalformedIfException.h"
#include "MalformedQuoteException.h"
#include "MalformedDefineException.h"
#include "MalformedLambdaException.h"
#include "EmptyExpressionException.h"
#include "InvalidEndOfExpressionException.h"
#include "UnbalancedParenthesesException.h"
#include "UnmatchedCloseParenthesisException.h"

using namespace std;

class Parser {

    /**
     * Parser for a generic expression.
     */
    static LObject* parseExpr(vector<string>& tokens) throw (ParserException, TokenizerException); 

    /**
     * Specific parsers for each type involved in the language.
     */
    static LObject* parseList(vector<string>& tokens) throw (ParserException, TokenizerException);
    static LObject* parseDefineExpression(vector<string>& tokens) throw (ParserException,TokenizerException); 
    static LObject* parseIfExpression(vector<string>& tokens) throw (ParserException, TokenizerException); 
    static LObject* parseLambdaExpression(vector<string>& tokens) throw (ParserException, TokenizerException);   
    static LObject* parseAtom(string& token) throw (ParserException, TokenizerException);
    static int parseInteger(string& token) throw (ParserException);
    static double parseDouble(string& token) throw (ParserException);

    /**
     * helpers
     */
    static vector<LSymbol*>* extractArgs(LCons *list);

public:
    
    /**
     * Parses and returns an object which represents the expression given
     * as argument.
     */
    static LObject* parse(string& input) throw (ParserException, TokenizerException);
};

#endif // __PARSER__

