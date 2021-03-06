#ifndef LISPINO_TOKENIZER_H_
#define LISPINO_TOKENIZER_H_

#include <iostream>

#include "Token.h"
#include "errors/CompileError.h"

namespace lispino {

class Tokenizer {
 public:
  explicit Tokenizer(std::istream& input_stream);

  void enableQuotation();
  void disableQuotation();

  // parses and returns the next token
  Token* next() throw(errors::CompileError);

 private:
  // the reference to the stream from which the tokens will be parsed
  std::istream &stream;

  // the current position in the source code
  SourceCodePosition position;

  // flag used to control the quotation
  bool quotationEnabled;

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
  Token* string() throw(errors::CompileError);
};
}

#endif  // LISPINO_TOKENIZER_H_
