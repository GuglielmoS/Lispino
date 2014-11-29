#ifndef LISPINO_PARSER_H_
#define LISPINO_PARSER_H_

#include <iostream>

#include "VM.h"
#include "Object.h"
#include "Tokenizer.h"
#include "errors/CompileError.h"

namespace lispino {

class Parser {
 public:
  explicit Parser(std::istream& input_stream);

  Object* parse() throw(errors::CompileError);

  Object* parseExpr() throw(errors::CompileError);

 private:
  Allocator &allocator;

  Tokenizer tokenizer;

  std::string current_context;

  Object* parseList() throw(errors::CompileError);

  Object* parseIf() throw(errors::CompileError);

  Object* parseCond() throw(errors::CompileError);

  Object* parseLambda() throw(errors::CompileError);

  Object* parseLet() throw(errors::CompileError);

  Object* parseDefine() throw(errors::CompileError);

  Object* parseQuote(bool check_paren = true) throw(errors::CompileError);

  Object* parseBegin() throw(errors::CompileError);

  Object* dispatch(Token *token) throw(errors::CompileError);

  void check(Token *token, TokenType expected_type) throw(errors::CompileError);

  void checkExpr(Token* token, TokenType suggested_type) throw(errors::CompileError);

  void setContext(std::string&& context);

  void resetContext();

  std::string& getContext();
};
}

#endif // LISPINO_PARSER_H_
