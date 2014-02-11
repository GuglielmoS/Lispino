#include "Token.h"

#include <string>
#include <algorithm>

using namespace Lispino;

// initialize the reserved keywords map
std::map<std::string, TokenType> Token::reservedKeywords = Token::initializeReservedKeywords();

std::map<std::string, TokenType> Token::initializeReservedKeywords() {
    static std::map<std::string, TokenType> bindings;
    
    bindings["nil"]    = TokenType::NIL;
    bindings["lambda"] = TokenType::LAMBDA;
    bindings["define"] = TokenType::DEFINE;
    bindings["quote"]  = TokenType::QUOTE;
    bindings["true"]   = TokenType::BOOL_TRUE;
    bindings["false"]  = TokenType::BOOL_FALSE;
    bindings["if"]     = TokenType::IF;

    return bindings;
}

Token::Token(TokenType type, std::string value) { 
    std::string tempValue = value;
    std::transform(tempValue.begin(), tempValue.end(), tempValue.begin(), ::tolower);

    std::map<std::string, TokenType>::iterator it = reservedKeywords.find(tempValue);

    if (it != reservedKeywords.end()) {
        this->type = it->second;
        this->rawValue = std::string();
    }
    else {
        this->type = type;
        this->rawValue = value;
    }
}
