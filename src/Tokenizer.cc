#include "Tokenizer.h"

#include <cctype>
#include <cstdlib>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>

namespace Lispino {

Tokenizer::Tokenizer(std::istream& input_stream) : stream(input_stream) {
  /* DO NOTHING */
}

Token* Tokenizer::next() throw (Errors::CompileError) {
  Token *current_token = nullptr;

  // skip the comments (;; blah blah) and the various spaces (\n, ' ', \t ...)
  skipCommentsAndSpaces();

  // try to parse the next token
  if ((current_token = delimiter()) != nullptr)
    return current_token;
  else if ((current_token = number()) != nullptr)
    return current_token;
  else if ((current_token = symbol()) != nullptr)
    return current_token;
  else if ((current_token = string()) != nullptr)
    return current_token;
  else
    return new Token(TokenType::UNKNOWN);
}

int Tokenizer::get() {
  return stream.get();
}

char Tokenizer::nextChar() {
  return static_cast<char>(get());
}

void Tokenizer::unget() {
  stream.unget();
}

void Tokenizer::putback(int ch) {
  stream.putback(ch);
}

void Tokenizer::skipSpaces() {
  while (isspace(nextChar())) continue; 
  unget();
}

void Tokenizer::skipCommentsAndSpaces() {
  // skip the initial spaces
  skipSpaces();

  // loop until no other comments are found
  while (nextChar() == ';') {
    // skip the characters between the ';' and the newline
    while (nextChar() != '\n') continue;

    // skip the other eventual spaces
    skipSpaces();
  }

  // put the last char found on the stream because it has not been used
  unget();
}

bool Tokenizer::isdelimiter(char ch) const {
  return ch == EOF ||
         ch == '(' || 
         ch == ')' || 
         ch == '.' || 
         ch == '\'';
}

Token* Tokenizer::delimiter() {
  int ch = get();
  switch (ch) {
    case EOF:  return new Token(TokenType::EOS);
    case '(':  return new Token(TokenType::OPEN_PAREN);
    case ')':  return new Token(TokenType::CLOSE_PAREN);
    case '.':  return new Token(TokenType::DOT);
    case '\'': return new Token(TokenType::SMART_QUOTE);
  }
  unget();

  return nullptr;
}

Token* Tokenizer::symbol() {
  std::stringstream buffer;

  char ch = nextChar();
  if (!isdigit(ch)) {
    while (!isspace(ch) && !isdelimiter(ch) && ch != '"') {
      buffer << ch;
      ch = nextChar();
    }
  }
  unget();

  if (buffer.str().size() == 0)
    return nullptr;
  else
    return new Token(TokenType::SYMBOL, buffer.str());
}

Token* Tokenizer::number() {
  std::stringstream buffer;
  bool isFloat = false;
  bool negate = false;

  // check for the initial minus sign
  char ch = nextChar();
  if (ch == '-') {
    negate = true;

    if (isdigit(ch = nextChar())) {
      buffer << ch;
    } else {
      unget();
      putback('-');
      return nullptr;
    }
  } else if (isdigit(ch)) {
    buffer << ch;
  } else {
    unget();
    return nullptr;
  }

  // parse the integer part
  while (isdigit(ch = nextChar()))
    buffer << ch;

  // if this is a float, parse the decimal part
  if (buffer.str().size() > 0 && ch == '.') {
    isFloat = true;
    buffer << ch;

    while (isdigit(ch = nextChar()))
      buffer << ch;
  }

  // recover the stream status
  unget();

  if (buffer.str().size() == 0) { 
    return nullptr;
  } else {
    if (isFloat) {
      double value = std::stof(buffer.str()); 
      if (negate)
        return new Token(-value);
      else
        return new Token(value);
    } else {
      std::int64_t value = stol(buffer.str());
      if (negate)
        return new Token(-value);
      else
        return new Token(value);
    }
  }
}

Token* Tokenizer::string() throw (Errors::CompileError) {
  std::stringstream buffer;

  if (nextChar() != '"') {
    unget();
    return nullptr;
  }

  bool escape = false;
  while (true) {
    int raw_ch = get();
    char ch = static_cast<char>(raw_ch);

    if (ch == EOF) {
      throw Errors::CompileError(/*"Unterminated string*/);
    } else if (ch == '\\') {
      escape = true;
    } else if (ch == '"') {
      if (escape) {
        escape = false;
        buffer << ch;
      } else {
        break;
      }
    } else {
      char ch_to_put = ch;

      // handle the escaping
      if (escape) {
        escape = false;

        switch (ch) {
          case 'n':  
            ch_to_put = '\n';
            break;
          case 'r':
            ch_to_put = '\r';
            break;
          case '\\':
            ch_to_put = '\\';
            break;
          default:
            buffer << '\\';
        }
      }

      // put the read character in the buffer
      buffer << ch_to_put;
    }
  }

  return new Token(TokenType::STRING, buffer.str());
}

}
