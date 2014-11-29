#ifndef LISPINO_TOKEN_H_
#define LISPINO_TOKEN_H_

#include <cstdlib>
#include <cstdint>

#include <iostream>
#include <string>
#include <map>

#include "SourceCodePosition.h"

namespace lispino {

enum class TokenType {
  EOS,
  OPEN_PAREN, CLOSE_PAREN, DOT, SMART_QUOTE,
  CHARACTER,
  SYMBOL,
  INT_NUMBER,
  FLOAT_NUMBER,
  STRING,
  //RESERVED_KEYWORDS_START__,
  NIL,
  LAMBDA,
  LET,
  DEFINE,
  QUOTE,
  IF,
  BOOL_TRUE, BOOL_FALSE,
  COND,
  BEGIN,
  //RESERVED_KEYWORDS_END__,
  UNKNOWN
};

class Token {
 public:
  TokenType getType() const;

  char getCharacter() const;

  std::string getSymbol() const;

  std::string getString() const;

  std::int64_t getIntNumber() const;

  double getFloatNumber() const;

  SourceCodePosition getSourceCodePosition() const;

  // factory methods
  static Token* create(TokenType type, SourceCodePosition position);
  static Token* createCharacter(char value, SourceCodePosition position);
  static Token* createIntNumber(std::int64_t value, SourceCodePosition position);
  static Token* createFloatNumber(double value, SourceCodePosition position);
  static Token* createString(std::string value, SourceCodePosition position);
  static Token* createSymbol(std::string value, SourceCodePosition position);

 private:
  TokenType type;

  char char_value;

  std::string raw_value;

  std::int64_t int_value;

  double float_value;

  SourceCodePosition position;

  // the constructor is private because only the specialized static methods
  // must be used for creating a Token
  Token();

  // it contains all the reserved keywords and their relative TokenType
  static std::map<std::string, TokenType> reserved_keywords;

  // populates the reserved keywords map
  static std::map<std::string, TokenType> initializeReservedKeywords();
};
}

#endif // LISPINO_TOKEN_H_
