#ifndef __TOKEN_H__
#define __TOKEN_H__

// Standard C++ headers
#include <iostream>
#include <cstdlib>
#include <string>
#include <map>

namespace Lispino {

    enum TokenType {EOS,
                    OPEN_PAREN, CLOSE_PAREN, DOT,
                    SYMBOL,
                    INT_NUMBER,
                    FLOAT_NUMBER,
                    STRING,
                    //RESERVED_KEYWORDS_START__,
                    NIL,
                    LAMBDA,
                    DEFINE,
                    QUOTE,
                    //RESERVED_KEYWORDS_END__,
                    UNKNOWN};

    class Token {

        TokenType type;
        std::string rawValue;

        // it contains all the reserved keywords and their relative TokenType
        static std::map<std::string, TokenType> reservedKeywords;
        
        // populates the reserved keywords map
        static std::map<std::string, TokenType> initializeReservedKeywords();

        public:

            Token(TokenType type) :
                type(type), rawValue(std::string()) {}

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
                return atol(rawValue.c_str());
            }

            float getFloatNumber() const {
                return atof(rawValue.c_str());
            }

    };
};

#endif // __TOKEN_H__
