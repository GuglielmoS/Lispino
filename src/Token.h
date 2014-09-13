#ifndef LISPINO_TOKEN_H_
#define LISPINO_TOKEN_H_

#include <iostream>
#include <cstdlib>
#include <string>
#include <map>

namespace Lispino {

enum TokenType {
  EOS,
  OPEN_PAREN, CLOSE_PAREN, DOT, SMART_QUOTE,
  SYMBOL,
  INT_NUMBER,
  FLOAT_NUMBER,
  STRING,
  //RESERVED_KEYWORDS_START__,
  NIL,
  LAMBDA,
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

  Token(long int value);

  Token(float value);

  Token(TokenType type, std::string value);

  TokenType getType() const;
  
  std::string getSymbol() const;
  
  std::string getString() const;
  
  long int getIntNumber() const;
  
  float getFloatNumber() const;

 private:
  TokenType type;

  std::string raw_value;

  long int int_value;

  float float_value;

  // it contains all the reserved keywords and their relative TokenType
  static std::map<std::string, TokenType> reserved_keywords;

  // populates the reserved keywords map
  static std::map<std::string, TokenType> initializeReservedKeywords();
};

}

#endif // LISPINO_TOKEN_H_
