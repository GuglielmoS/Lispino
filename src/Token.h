#ifndef LISPINO_TOKEN_H_
#define LISPINO_TOKEN_H_

#include <cstdlib>
#include <cstdint>

#include <iostream>
#include <string>
#include <map>

namespace Lispino {

enum class TokenType {
  EOS,
  OPEN_PAREN, CLOSE_PAREN, DOT, SMART_QUOTE,
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
  //RESERVED_KEYWORDS_END__,
  UNKNOWN
};

class Token {
 public:
  Token(TokenType type);

  Token(std::int64_t value);

  Token(double value);

  Token(TokenType type, std::string value);

  TokenType getType() const;
  
  std::string getSymbol() const;
  
  std::string getString() const;
  
  std::int64_t getIntNumber() const;
  
  double getFloatNumber() const;

 private:
  TokenType type;

  std::string raw_value;

  std::int64_t int_value;

  double float_value;

  // it contains all the reserved keywords and their relative TokenType
  static std::map<std::string, TokenType> reserved_keywords;

  // populates the reserved keywords map
  static std::map<std::string, TokenType> initializeReservedKeywords();
};

}

#endif // LISPINO_TOKEN_H_
