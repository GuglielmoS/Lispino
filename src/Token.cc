#include "Token.h"

#include <string>
#include <algorithm>

namespace Lispino {

// initialize the reserved keywords map
std::map<std::string, TokenType> Token::reserved_keywords = Token::initializeReservedKeywords();

Token::Token(TokenType type)
    : type(type), 
      raw_value(std::string()), 
      int_value(0),
      float_value(0.0) {
  /* DO NOTHING */
}

Token::Token(long int value)
    : type(INT_NUMBER),
      raw_value(std::string()),
      int_value(value),
      float_value(0.0) {
  /* DO NOTHING */
}

Token::Token(float value)
    : type(FLOAT_NUMBER),
      raw_value(std::string()),
      int_value(0),
      float_value(value) {
  /* DO NOTHING */
}

Token::Token(TokenType type, std::string value) { 
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

long int Token::getIntNumber() const {
  return int_value;
}

float Token::getFloatNumber() const {
  return float_value;
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
