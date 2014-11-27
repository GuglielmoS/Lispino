#include "Token.h"

#include <string>
#include <algorithm>

namespace Lispino {

// initialize the reserved keywords map
std::map<std::string, TokenType> Token::reserved_keywords = Token::initializeReservedKeywords();

TokenType Token::getType() const {
  return type;
}

char Token::getCharacter() const {
  return char_value;
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

Token* Token::create(TokenType type, SourceCodePosition position) {
  Token *tok = new Token();

  tok->type = type;
  tok->position = position;

  return tok;
}

Token* Token::createCharacter(char value, SourceCodePosition position) {
  Token *tok = create(TokenType::CHARACTER, position);

  tok->char_value = value;

  return tok;
}

Token* Token::createIntNumber(std::int64_t value, SourceCodePosition position) {
  Token *tok = create(TokenType::INT_NUMBER, position);

  tok->int_value = value;

  return tok;
}

Token* Token::createFloatNumber(double value, SourceCodePosition position) {
  Token *tok = create(TokenType::FLOAT_NUMBER, position);

  tok->float_value = value;

  return tok;
}

Token* Token::createString(std::string value, SourceCodePosition position) {
  Token *tok = create(TokenType::STRING, position);

  tok->raw_value = value;

  return tok;
}

Token* Token::createSymbol(std::string value, SourceCodePosition position) {
  Token *tok = create(TokenType::SYMBOL, position);

  std::string temp_value = value;
  std::transform(temp_value.begin(), temp_value.end(), temp_value.begin(), ::tolower);

  auto it = reserved_keywords.find(temp_value);
  if (it != reserved_keywords.end()) {
    tok->type = it->second;
    tok->raw_value = std::string();
  }
  else {
    tok->raw_value = value;
  }

  return tok;
}

// private constructor
Token::Token() {
  // DO NOTHING
}

}
