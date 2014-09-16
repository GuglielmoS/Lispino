#include "Parser.h"

#include <vector>
#include <memory>

namespace Lispino {

Parser::Parser(std::istream& inputStream)
    : allocator(VM::getAllocator()), 
      tokenizer(inputStream) {
  /* DO NOTHING */    
}

Object* Parser::parse() {
  Object *expr = parseExpr();

  // check for the End Of Stream
  std::unique_ptr<Token> token(tokenizer.next());
  if (token->getType() != TokenType::EOS)
    throw std::runtime_error("PARSER - missing End Of Stream!");

  return expr;
}

Object* Parser::parseExpr() {
  std::unique_ptr<Token> token(tokenizer.next());
  return dispatch(token.get());
}

Object* Parser::parseList() { 
  std::unique_ptr<Token> token(tokenizer.next());
  Object *head = nullptr;

  // check if the current token is a reserved keyword or the end of the list
  switch (token->getType()) {
    case TokenType::CLOSE_PAREN: return allocator.createNil();  // empty list == nil
    case TokenType::LAMBDA:      return parseLambda();          // lambda
    case TokenType::LET:         return parseLet();             // let == lexical closure
    case TokenType::DEFINE:      return parseDefine();          // define
    case TokenType::QUOTE:       return parseQuote();           // quote
    case TokenType::IF:          return parseIf();              // if
    case TokenType::COND:        return parseCond();            // cond
    default:                     head = dispatch(token.get());  // other
  }

  // create the final list
  List *result = allocator.createList(head, allocator.createNil());
  List *current = result;
  bool improper_list = false;

  // parse the tail if needed
  token.reset(tokenizer.next());
  while (token->getType() != TokenType::CLOSE_PAREN) {
    if (token->getType() == TokenType::DOT) {
      improper_list = true;
      token.reset(tokenizer.next());
    }

    if (improper_list) {
      current->setRest(dispatch(token.get()));
      improper_list = false;
    }
    else {
      current->setRest(allocator.createList(dispatch(token.get()), allocator.createNil()));
      current = static_cast<List*>(current->getRest());
    }

    token.reset(tokenizer.next());
  }

  return result;
}

Object* Parser::parseIf() {
  // parse the condition
  Object *condition = parseExpr();

  // parse the consequent expression
  Object *consequent = parseExpr();

  // parse the alternative if needed
  Object *alternative = nullptr;
  std::unique_ptr<Token> token(tokenizer.next());
  if (token->getType() != TokenType::CLOSE_PAREN)
    alternative = dispatch(token.get());
  else
    alternative = allocator.createNil();

  // create the object
  Object *if_expr = allocator.createIf(condition, consequent, alternative);

  // check for the final paren ')'
  if (alternative != nullptr) {
    token.reset(tokenizer.next());
    if (token->getType() != TokenType::CLOSE_PAREN)
      throw std::runtime_error("PARSER - invalid IF arguments, missing ')'");
  }

  return if_expr;
}

Object* Parser::parseCond() {
  /*
   (cond ((<expr_1> <expr_1_body>)
          ...
          (<expr_n> <expr_n_body>)))

    is equivalent to

   (if <expr_1> <expr_1_body>
      ...
      (if <expr_n> <expr_n_body>
        nil))

   */

  std::unique_ptr<Token> token(tokenizer.next());
  IfExpr *first_if_expr = nullptr;
  IfExpr *current_if_expr = nullptr;
  
  // check the initial '(' of the conditions list
  if (token->getType() != TokenType::OPEN_PAREN)
    throw std::runtime_error("PARSER - invalid COND, missing '('");

  // skip to the next token
  token.reset(tokenizer.next());
  while (token->getType() == TokenType::OPEN_PAREN) {
    // parse the current condition expr
    Object *condition_expr = parseExpr();

    // parse the expr associated to the current condition
    Object *associated_expr = parseExpr();

    // build the new if expression
    IfExpr *new_if_expr = allocator.createIf(condition_expr, associated_expr, allocator.createNil());

    // bind the new IF the previous one
    if (first_if_expr == nullptr) {
      first_if_expr = new_if_expr;
      current_if_expr = first_if_expr;
    } else {
      current_if_expr->setAlternative(new_if_expr);
      current_if_expr = new_if_expr;
    }

    // check the current binding final ')'
    token.reset(tokenizer.next());
    if (token->getType() != TokenType::CLOSE_PAREN)
      throw std::runtime_error("PARSER - invalid COND, missing ')'");

    // skip to the next token
    token.reset(tokenizer.next());
  }

  // check the final ')' of the conditions list
  if (token->getType() != TokenType::CLOSE_PAREN)
    throw std::runtime_error("PARSER - invalid COND, missing ')'");
  
  // check the final ')' of the COND expr
  token.reset(tokenizer.next());
  if (token->getType() != TokenType::CLOSE_PAREN)
    throw std::runtime_error("PARSER - invalid COND, missing ')'");

  return first_if_expr;
}

Object* Parser::parseLambda() {
  // parse the arguments
  std::unique_ptr<Token> token(tokenizer.next());
  std::vector<std::string> params;

  if (token->getType() != TokenType::OPEN_PAREN)
    throw std::runtime_error("PARSER - invalid LAMBDA arguments, missing '('");

  token.reset(tokenizer.next());
  while (token->getType() == TokenType::SYMBOL) {
    params.push_back(token->getSymbol());
    token.reset(tokenizer.next());
  }

  if (token->getType() != TokenType::CLOSE_PAREN)
    throw std::runtime_error("PARSER - invalid LAMBDA arguments, missing ')'");

  // parse the body
  Object *body = parseExpr();

  // check the ')'
  token.reset(tokenizer.next());
  if (token->getType() != TokenType::CLOSE_PAREN)
    throw std::runtime_error("PARSER - invalid LAMBDA arguments, missing ')'");

  return allocator.createLambda(body, params);
}

Object* Parser::parseLet() {
  // parse the arguments
  std::unique_ptr<Token> token(tokenizer.next());

  // check the bindings list intial '('
  if (token->getType() != TokenType::OPEN_PAREN)
    throw std::runtime_error("PARSER - invalid LET arguments, missing '('");

  // parse the LET bindings ([symbol -> value] pairs)
  std::vector<std::string> let_symbols;
  std::vector<Object*> let_values;

  // skip to the next token
  token.reset(tokenizer.next());
  while (token->getType() == TokenType::OPEN_PAREN) {
    // parse the current binding symbol
    token.reset(tokenizer.next());
    if (token->getType() != TokenType::SYMBOL)
      throw std::runtime_error("PARSER - invalid LET arguments, missing a symbol in the bindings list");
    let_symbols.push_back(token->getSymbol());

    // parse the current binding value
    let_values.push_back(parseExpr());

    // check the current binding final ')'
    token.reset(tokenizer.next());
    if (token->getType() != TokenType::CLOSE_PAREN)
      throw std::runtime_error("PARSER - invalid LET arguments, missing ')'");

    // skip to the next token
    token.reset(tokenizer.next());
  }

  // check the bindings list final ')'
  if (token->getType() != TokenType::CLOSE_PAREN)
    throw std::runtime_error("PARSER - invalid LET arguments, missing ')'");

  // parse the body of the LET expression
  Object *body = parseExpr();

  // check the final ')'
  token.reset(tokenizer.next());
  if (token->getType() != TokenType::CLOSE_PAREN)
    throw std::runtime_error("PARSER - invalid LET arguments, missing ')'");

  // create the lambda with the LET body and the LET symbols
  Lambda *let_lambda = allocator.createLambda(body, let_symbols);

  // return the application of the LET values to the LET lambda
  return allocator.createList(let_lambda, vec2cons(let_values));
}

Object* Parser::parseDefine() {
  std::unique_ptr<Token> token(tokenizer.next());
  std::vector<std::string> params;
  std::string name;
  bool isFunction = true;

  if (token->getType() == TokenType::OPEN_PAREN) {
    bool isFirst = true;

    token.reset(tokenizer.next());
    while (token->getType() == TokenType::SYMBOL) {
      if (isFirst) {
        isFirst = false;
        name = token->getSymbol();
      } else {
        params.push_back(token->getSymbol());
      }

      token.reset(tokenizer.next());
    }

    if (isFirst)
      throw std::runtime_error("PARSER - invalid DEFINE arguments, missing SYMBOL");
    else if (token->getType() != TokenType::CLOSE_PAREN)
      throw std::runtime_error("PARSER - invalid DEFINE arguments, missing ')'");

  } else if (token->getType() == TokenType::SYMBOL) {
    isFunction = false;
    name = token->getSymbol();
  } else {
    throw std::runtime_error("PARSER - invalid DEFINE arguments, missing SYMBOL");
  }

  // parse the define expressions
  std::vector<Object*> expressions;
  token.reset(tokenizer.next());
  while (token->getType() != TokenType::CLOSE_PAREN) {
    expressions.push_back(dispatch(token.get()));
    token.reset(tokenizer.next());
  }

  // check for the final paren ')'
  if (token->getType() != TokenType::CLOSE_PAREN)
    throw std::runtime_error("PARSER - invalid DEFINE body, missing ')'");

  // create and optimize the define body if possible
  Object* value = nullptr;
  if (expressions.size() == 0)
    throw std::runtime_error("PARSER - invalid DEFINE body, it's empty!");
  else if (expressions.size() == 1)
    value = expressions[0];
  else
    value = allocator.createSequence(expressions);

  // return the proper definition object
  if (isFunction)
    return allocator.createDefine(name, allocator.createLambda(value, params));
  else
    return allocator.createDefine(name, value);
}

Object* Parser::parseQuote() {
  Object *quote = allocator.createQuote(parseExpr());

  // check for the final paren ')'
  std::unique_ptr<Token> token(tokenizer.next());
  if (token->getType() != TokenType::CLOSE_PAREN)
    throw std::runtime_error("PARSER - invalid QUOTE arguments, missing ')'");

  return quote;
}

Object* Parser::dispatch(Token *token) {
  switch (token->getType()) {
    case TokenType::NIL:          return allocator.createNil();
    case TokenType::SYMBOL:       return allocator.createSymbol(token->getSymbol());
    case TokenType::STRING:       return allocator.createString(token->getString());
    case TokenType::INT_NUMBER:   return allocator.createIntNumber(token->getIntNumber());
    case TokenType::FLOAT_NUMBER: return allocator.createFloatNumber(token->getFloatNumber());
    case TokenType::BOOL_TRUE:    return allocator.createBoolean(true);
    case TokenType::BOOL_FALSE:   return allocator.createBoolean(false);
    case TokenType::SMART_QUOTE:  return allocator.createQuote(parseExpr());
    case TokenType::OPEN_PAREN:   return parseList();
    case TokenType::EOS:          return nullptr;
    default:                      throw std::runtime_error("PARSER - dispatch failed");
  }
}

Object* Parser::vec2cons(std::vector<Object*>& objects) {
  List *last_cons = nullptr;
  List *first_cons = nullptr;

  for (auto& current_object : objects) {
    List *new_cons = allocator.createList(current_object, allocator.createNil());

    if (last_cons == nullptr) {
      first_cons = new_cons;
      last_cons = new_cons;
    } else {
      last_cons->setRest(new_cons);
      last_cons = static_cast<List*>(last_cons->getRest());
    }
  }

  if (first_cons == nullptr)
    return allocator.createNil();
  else
    return first_cons;
}

}
