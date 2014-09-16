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

  Object* parseList();

  Object* parseIf();

  Object* parseCond();
  
  Object* parseLambda();

  Object* parseLet();
  
  Object* parseDefine();
  
  Object* parseQuote();

  Object* parseBegin();
  
  Object* dispatch(Token *token);

  Object* vec2cons(std::vector<Object*>& objects);
};

}

#endif // LISPINO_PARSER_H_
