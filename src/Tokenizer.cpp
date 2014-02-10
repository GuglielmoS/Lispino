// Internal headers
#include "Tokenizer.h"

// Standard C++ headers
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <memory>
#include <cstdlib>

using namespace Lispino;

void Tokenizer::skipSpaces() {
    while (isspace((char)stream->get())) { /* DO NOTHING */ }
    stream->unget();
}

bool Tokenizer::isdelimiter(char ch) const {
    return ch == EOF || ch == '(' || ch == ')' || ch == '.';
}

Token* Tokenizer::delimiter() {
    int ch = stream->get();
    switch (ch) {
        case EOF: return new Token(TokenType::EOS);
        case '(': return new Token(TokenType::OPEN_PAREN);
        case ')': return new Token(TokenType::CLOSE_PAREN);
        case '.': return new Token(TokenType::DOT);
    }
    stream->unget();

    return nullptr;
}

Token* Tokenizer::symbol() {
    std::stringstream buffer;
    
    char ch = stream->get();
    if (!isdigit(ch)) {
        while (!isspace(ch) && !isdelimiter(ch) && ch != '"') {
            buffer << ch;
            ch = stream->get();
        }
    }
    stream->unget();

    return (buffer.str().size() == 0) ? nullptr : new Token(TokenType::SYMBOL, buffer.str());
}

Token* Tokenizer::number() {
    std::stringstream buffer;
    bool isFloat = false;
    char ch;

    while (isdigit(ch = stream->get()))
        buffer << ch;
    
    // if this is a float
    if (buffer.str().size() > 0 && ch == '.') {
        isFloat = true;
        buffer << ch;
        
        while (isdigit(ch = stream->get()))
            buffer << ch;
    }
    
    // recover the stream status
    stream->unget();

    if (buffer.str().size() == 0) 
        return nullptr;
    else
        return new Token(isFloat ? TokenType::FLOAT_NUMBER : TokenType::INT_NUMBER, buffer.str());
}

Token* Tokenizer::string() {
    std::stringstream buffer;

    char ch = stream->get();

    if (ch != '"') {
        stream->unget();
        return nullptr;
    }

    bool escape = false;
    while (true) {
        ch = stream->get();

        if (ch == '\\')
            escape = true;
        else if (ch == '"') {
            if (escape) {
                escape = false;
                buffer << ch;
            }
            else
                break;
        }
        else
            buffer << ch;
    }

    if (ch != '"') {
        std::cerr << "UNTERMINATED STRING!" << std::endl;
        return nullptr;
    }

    return new Token(TokenType::STRING, buffer.str());
}

Token* Tokenizer::next() {
    Token *currentToken;

    // skip various spaces (\n, ' ', \t ...)
    skipSpaces();

    // try to parse the next token
    if ((currentToken = delimiter()) != nullptr)
        return currentToken;
    else if ((currentToken = symbol()) != nullptr)
        return currentToken;
    else if ((currentToken = number()) != nullptr)
        return currentToken;
    else if ((currentToken = string()) != nullptr)
        return currentToken;
    else
        return new Token(TokenType::UNKNOWN);
}
