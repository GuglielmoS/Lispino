#include "Token.h"

#include <string>
#include <algorithm>

namespace Lispino {

// initialize the reserved keywords map
std::map<std::string, TokenType> Token::reserved_keywords = Token::initializeReservedKeywords();

Token::Token(TokenType type, SourceCodePosition position)
    : type(type), 
      raw_value(std::string()), 
      int_value(0),
      float_value(0.0),
      position(position) {
  /* DO NOTHING */
}

Token::Token(std::int64_t value, SourceCodePosition position)
    : type(TokenType::INT_NUMBER),
      raw_value(std::string()),
      int_value(value),
      float_value(0.0),
      position(position) {
  /* DO NOTHING */
}

Token::Token(double value, SourceCodePosition position)
    : type(TokenType::FLOAT_NUMBER),
      raw_value(std::string()),
      int_value(0),
      float_value(value),
      position(position) {
  /* DO NOTHING */
}

Token::Token(TokenType type, std::string value, SourceCodePosition position)
    : position(position) { 
  std::string temp_value = value;
  std::transform(temp_value.begin(), temp_value.end(), temp_value.begin(), ::tolower);

  auto it = reserved_keywords.find(temp_value);
  if (it != reserved_keywords.end()) {
    this->type = it->second;
    this->raw_value = std::string();
  }
  else {
    this->type = type;
    this->raw_value = value;
  }
}

TokenType Token::getType() const {
  return type;
}

std::string Token::getSymbol() const {
  return raw_value;
}

std::string Token::getString() const {
  return raw_value;
}

std::int64_t Token::getIntNumber() const {
  return int_value;
}

double Token::getFloatNumber() const {
  return float_value;
}

SourceCodePosition Token::getSourceCodePosition() const {
  return position;
}

std::map<std::string, TokenType> Token::initializeReservedKeywords() {
  static std::map<std::string, TokenType> bindings;

  bindings["nil"]    = TokenType::NIL;
  bindings["lambda"] = TokenType::LAMBDA;
  bindings["let"]    = TokenType::LET;
  bindings["define"] = TokenType::DEFINE;
  bindings["quote"]  = TokenType::QUOTE;
  bindings["#t"]   = TokenType::BOOL_TRUE;
  bindings["#f"]  = TokenType::BOOL_FALSE;
  bindings["if"]     = TokenType::IF;
  bindings["cond"]   = TokenType::COND;
  bindings["begin"]  = TokenType::BEGIN;

  return bindings;
}

}
