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

  std::string current_context;

  Object* parseList() throw (Errors::CompileError);

  Object* parseIf() throw (Errors::CompileError);

  Object* parseCond() throw (Errors::CompileError);
  
  Object* parseLambda() throw (Errors::CompileError);

  Object* parseLet() throw (Errors::CompileError);
  
  Object* parseDefine() throw (Errors::CompileError);
  
  Object* parseQuote(bool check_paren = true) throw (Errors::CompileError);

  Object* parseBegin() throw (Errors::CompileError);
  
  Object* dispatch(Token *token) throw (Errors::CompileError);

  void check(Token *token, TokenType expected_type) throw (Errors::CompileError);

  void setContext(std::string&& context);

  void resetContext();

  std::string& getContext();
};

}

#endif // LISPINO_PARSER_H_
