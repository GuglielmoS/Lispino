#ifndef LISPINO_TOKENIZER_H_
#define LISPINO_TOKENIZER_H_

#include <iostream>

#include "Token.h"
#include "errors/CompileError.h"

namespace Lispino {

class Tokenizer {
 public:
  Tokenizer(std::istream& input_stream);

  // parses and returns the next token
  Token* next() throw (Errors::CompileError);

 private:
  // the reference to the stream from which the tokens will be parsed
  std::istream &stream;

  // the current position in the source code
  SourceCodePosition position;

  // retrieve the next element from the input stream
  int get();
  char nextChar();

  // put on the input stream the last element retrieved
  void unget();

  // put on the input stream the specified element
  void putback(int ch);

  // eat all the spaces
  void skipSpaces();

  // skip all the comments and spaces
  void skipCommentsAndSpaces();

  // useful predicates
  bool isdelimiter(char ch) const;

  // sub-tokenizers
  Token* delimiter();
  Token* character();
  Token* symbol();
  Token* number();
  Token* string() throw (Errors::CompileError);
};

}

#endif // LISPINO_TOKENIZER_H_
