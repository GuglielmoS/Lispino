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

Token* Tokenizer::next() {
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

void Tokenizer::skipSpaces() {
  while (isspace((char)stream.get())) continue; 
  stream.unget();
}

void Tokenizer::skipCommentsAndSpaces() {
  // skip the initial possible spaces
  skipSpaces();

  // check if there is a starting comment
  if (stream.get() == ';') {
    if (stream.get() == ';') {
    // skip the current comment
    while (stream.get() != '\n') continue;

    // try to skip the comment on the next line
    skipCommentsAndSpaces();
    } else {
      stream.putback(';');
      stream.unget();
    }
  } else {
    stream.unget();
  }
}

bool Tokenizer::isdelimiter(char ch) const {
  return ch == EOF || ch == '(' || ch == ')' || ch == '.' || ch == '\'';
}

Token* Tokenizer::delimiter() {
  int ch = stream.get();
  switch (ch) {
    case EOF:  return new Token(TokenType::EOS);
    case '(':  return new Token(TokenType::OPEN_PAREN);
    case ')':  return new Token(TokenType::CLOSE_PAREN);
    case '.':  return new Token(TokenType::DOT);
    case '\'': return new Token(TokenType::SMART_QUOTE);
  }
  stream.unget();

  return nullptr;
}

Token* Tokenizer::symbol() {
  std::stringstream buffer;

  char ch = stream.get();
  if (!isdigit(ch)) {
    while (!isspace(ch) && !isdelimiter(ch) && ch != '"') {
      buffer << ch;
      ch = stream.get();
    }
  }
  stream.unget();

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
  char ch = stream.get();
  if (ch == '-') {
    negate = true;

    if (isdigit(ch = stream.get())) {
      buffer << ch;
    } else {
      stream.unget();
      stream.putback('-');
      return nullptr;
    }
  } else if (isdigit(ch)) {
    buffer << ch;
  } else {
    stream.unget();
    return nullptr;
  }

  // parse the integer part
  while (isdigit(ch = stream.get()))
    buffer << ch;

  // if this is a float, parse the decimal part
  if (buffer.str().size() > 0 && ch == '.') {
    isFloat = true;
    buffer << ch;

    while (isdigit(ch = stream.get()))
      buffer << ch;
  }

  // recover the stream status
  stream.unget();

  if (buffer.str().size() == 0) { 
    return nullptr;
  } else {
    if (isFloat) {
      if (negate)
        return new Token(-atof(buffer.str().c_str())); 
      else
        return new Token(atof(buffer.str().c_str()));
    } else {
      if (negate)
        return new Token(-atol(buffer.str().c_str()));
      else
        return new Token(atol(buffer.str().c_str()));
    }
  }
}

Token* Tokenizer::string() {
  std::stringstream buffer;

  char ch = stream.get();
  if (ch != '"') {
    stream.unget();
    return nullptr;
  }

  bool escape = false;
  while (true) {
    ch = stream.get();

    if (ch == '\\') {
      escape = true;
    } else if (ch == '"') {
      if (escape) {
        escape = false;
        buffer << ch;
      } else {
        break;
      }
    } else {
      buffer << ch;
    }
  }

  if (ch != '"') {
    std::cerr << "UNTERMINATED STRING!" << std::endl;
    return nullptr;
  }

  return new Token(TokenType::STRING, buffer.str());
}

}
