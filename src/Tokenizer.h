#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

// Internal headers
#include "Token.h"

// Standard C++ headers
#include <iostream>

namespace Lispino {

    class Tokenizer {
        
        // the reference to the stream from which the tokens will be parsed
        std::istream* stream;

        // eat all the spaces
        void skipSpaces();

        // useful predicates
        bool isdelimiter(char ch) const;

        // sub-tokenizers
        Token* delimiter();
        Token* symbol();
        Token* number();
        Token* string();

        public:
        
            Tokenizer(std::istream* inputStream) : stream(inputStream) {}

            // parses and returns the next token
            Token* next();
    };
};

#endif // __TOKENIZER_H__
