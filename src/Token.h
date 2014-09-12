#ifndef LISPINO_TOKEN_H_
#define LISPINO_TOKEN_H_

#include <iostream>
#include <cstdlib>
#include <string>
#include <map>

namespace Lispino {

    enum TokenType {EOS,
                    OPEN_PAREN, CLOSE_PAREN, DOT, SMART_QUOTE,
                    SYMBOL,
                    INT_NUMBER,
                    FLOAT_NUMBER,
                    STRING,
                    //RESERVED_KEYWORDS_START__,
                    NIL,
                    LAMBDA,
                    DEFINE,
                    QUOTE,
                    IF,
                    BOOL_TRUE, BOOL_FALSE,
                    //RESERVED_KEYWORDS_END__,
                    UNKNOWN};

    class Token {

        TokenType type;
        std::string rawValue;
        long int intValue;
        float floatValue;

        // it contains all the reserved keywords and their relative TokenType
        static std::map<std::string, TokenType> reservedKeywords;
        
        // populates the reserved keywords map
        static std::map<std::string, TokenType> initializeReservedKeywords();

        public:

            Token(TokenType type) :
                type(type), rawValue(std::string()), intValue(0), floatValue(0.0) {}

            Token(long int value) :
                type(INT_NUMBER), rawValue(std::string()), intValue(value), floatValue(0.0) {}

            Token(float value) :
                type(FLOAT_NUMBER), rawValue(std::string()), intValue(0), floatValue(value) {}

            Token(TokenType type, std::string value);

            TokenType getType() const {
                return type;
            }

            std::string getSymbol() const {
                return rawValue;
            }

            std::string getString() const {
                return rawValue;
            }

            long int getIntNumber() const {
                return intValue;
            }

            float getFloatNumber() const {
                return floatValue;
            }

    };
};

#endif // LISPINO_TOKEN_H_
