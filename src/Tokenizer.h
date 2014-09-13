#ifndef LISPINO_TOKENIZER_H_
#define LISPINO_TOKENIZER_H_

#include <iostream>

#include "Token.h"

namespace Lispino {

class Tokenizer {
 public:
  Tokenizer(std::istream& inputStream);

  // parses and returns the next token
  Token* next();

 private:
  // the reference to the stream from which the tokens will be parsed
  std::istream &stream;

  // eat all the spaces
  void skipSpaces();

  // skip all the comments and spaces
  void skipCommentsAndSpaces();

  // useful predicates
  bool isdelimiter(char ch) const;

  // sub-tokenizers
  Token* delimiter();
  Token* symbol();
  Token* number();
  Token* string();
};

}

#endif // LISPINO_TOKENIZER_H_
