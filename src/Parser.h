#ifndef LISPINO_PARSER_H_
#define LISPINO_PARSER_H_

#include <iostream>

#include "VM.h"
#include "Object.h"
#include "Tokenizer.h"

namespace Lispino {

class Parser {
 public:
  Parser(std::istream& inputStream);

  Object* parse();

  Object* parseExpr();

 private:
  Allocator &allocator;

  Tokenizer tokenizer;

  Object* parseIf();
  
  Object* parseList();
  
  Object* parseLambda();
  
  Object* parseDefine();
  
  Object* parseQuote();
  
  Object* dispatch(Token *token);
};

}

#endif // LISPINO_PARSER_H_
