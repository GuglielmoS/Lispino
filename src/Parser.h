#ifndef LISPINO_PARSER_H_
#define LISPINO_PARSER_H_

#include <iostream>

#include "VM.h"
#include "Object.h"
#include "Tokenizer.h"
#include "errors/CompileError.h"

namespace Lispino {

class Parser {
 public:
  Parser(std::istream& input_stream);

  Object* parse() throw (Errors::CompileError);

  Object* parseExpr() throw (Errors::CompileError);

 private:
  Allocator &allocator;

  Tokenizer tokenizer;

  Object* parseList() throw (Errors::CompileError);

  Object* parseIf() throw (Errors::CompileError);

  Object* parseCond() throw (Errors::CompileError);
  
  Object* parseLambda() throw (Errors::CompileError);

  Object* parseLet() throw (Errors::CompileError);
  
  Object* parseDefine() throw (Errors::CompileError);
  
  Object* parseQuote() throw (Errors::CompileError);

  Object* parseBegin() throw (Errors::CompileError);
  
  Object* dispatch(Token *token) throw (Errors::CompileError);
};

}

#endif // LISPINO_PARSER_H_
