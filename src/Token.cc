#include "Token.h"

#include <string>
#include <algorithm>

namespace Lispino {

    // initialize the reserved keywords map
    std::map<std::string, TokenType> Token::reservedKeywords = Token::initializeReservedKeywords();

    Token::Token(TokenType type) :
        type(type), rawValue(std::string()), intValue(0), floatValue(0.0) {
        /* DO NOTHING */
    }

    Token::Token(long int value) :
        type(INT_NUMBER), rawValue(std::string()), intValue(value), floatValue(0.0) {
        /* DO NOTHING */
    }

    Token::Token(float value) :
        type(FLOAT_NUMBER), rawValue(std::string()), intValue(0), floatValue(value) {
        /* DO NOTHING */
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

    TokenType Token::getType() const {
        return type;
    }

    std::string Token::getSymbol() const {
        return rawValue;
    }

    std::string Token::getString() const {
        return rawValue;
    }

    long int Token::getIntNumber() const {
        return intValue;
    }

    float Token::getFloatNumber() const {
        return floatValue;
    }

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
}
