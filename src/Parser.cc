#include "Parser.h"

#include <vector>
#include <memory>

#include "utils/List.h"
#include "utils/Token.h"

namespace Lispino {

Parser::Parser(std::istream& input_stream)
    : allocator(VM::getAllocator()), 
      tokenizer(input_stream) {
  /* DO NOTHING */    
}

Object* Parser::parse() throw (Errors::CompileError) {
  Object *expr = parseExpr();

  // check for the End Of Stream
  std::unique_ptr<Token> token(tokenizer.next());
  check(token.get(), TokenType::EOS);

  return expr;
}

Object* Parser::parseExpr() throw (Errors::CompileError) {
  std::unique_ptr<Token> token(tokenizer.next());
  return dispatch(token.get());
}

Object* Parser::parseList() throw (Errors::CompileError) { 
  setContext("LIST");

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
    case TokenType::BEGIN:       return parseBegin();           // begin
    case TokenType::EOS:         throw Errors::CompileError("Malformed list, missing ')'", token->getSourceCodePosition());
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

    // dispatch the next token
    Object *nextExpr = dispatch(token.get());

    // if the token is invalid, signal an error
    if (nextExpr == nullptr)
      throw Errors::CompileError("Malformed list, missing ')'", token->getSourceCodePosition());

    if (improper_list) {
      current->setRest(nextExpr);
      improper_list = false;
    }
    else {
      current->setRest(allocator.createList(nextExpr, allocator.createNil()));
      current = static_cast<List*>(current->getRest());
    }

    token.reset(tokenizer.next());
  }

  resetContext();
  return result;
}

Object* Parser::parseIf() throw (Errors::CompileError) {
  setContext("IF");

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
    check(token.get(), TokenType::CLOSE_PAREN);
  }

  resetContext();
  return if_expr;
}

Object* Parser::parseCond() throw (Errors::CompileError) {
  setContext("COND");
  /*
   (cond (<expr_1> <expr_1_body>)
         ...
         (<expr_n> <expr_n_body>))

    is equivalent to

   (if <expr_1> <expr_1_body>
      ...
      (if <expr_n> <expr_n_body>
        nil))

   */

  std::unique_ptr<Token> token(tokenizer.next());
  IfExpr *first_if_expr = nullptr;
  IfExpr *current_if_expr = nullptr;
  
  // skip to the next token
  //token.reset(tokenizer.next());
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
    check(token.get(), TokenType::CLOSE_PAREN);

    // skip to the next token
    token.reset(tokenizer.next());
  }

  // check the final ')' of the COND expr
  check(token.get(), TokenType::CLOSE_PAREN);

  resetContext();
  return first_if_expr;
}

Object* Parser::parseLambda() throw (Errors::CompileError) {
  setContext("LAMBDA");

  // parse the arguments
  std::unique_ptr<Token> token(tokenizer.next());
  std::vector<std::string> params;
  bool catch_rest_flag = false;

  // if there is a "catch rest" argument
  if (token->getType() == TokenType::SYMBOL) {
    catch_rest_flag = true;
    params.push_back(token->getSymbol());
  } else {
    // check the '('
    check(token.get(), TokenType::OPEN_PAREN);

    // parse the arguments
    token.reset(tokenizer.next());
    while (token->getType() == TokenType::SYMBOL) {
      params.push_back(token->getSymbol());
      token.reset(tokenizer.next());

      // exit if the catch_rest argument has been catched
      if (catch_rest_flag)
        break;

      // check if there is a "catch rest" argument 
      if (token->getType() == TokenType::DOT) {
        catch_rest_flag = true;
        token.reset(tokenizer.next());
      }
    }

    // check the ')'
    check(token.get(), TokenType::CLOSE_PAREN);
  }

  // parse the body
  Object *body = parseExpr();

  // check the ')'
  token.reset(tokenizer.next());
  check(token.get(), TokenType::CLOSE_PAREN);

  resetContext();
  return allocator.createLambda(body, params, catch_rest_flag);
}

Object* Parser::parseLet() throw (Errors::CompileError) {
  setContext("LET");
  /*
    (let ((a 1) (b 2))
      (+ a b))

      is equivalent to

    ((lambda (a b) (+ a b)) 1 2)
  */

  // parse the arguments
  std::unique_ptr<Token> token(tokenizer.next());

  // check the bindings list intial '('
  check(token.get(), TokenType::OPEN_PAREN);

  // parse the LET bindings ([symbol -> value] pairs)
  std::vector<std::string> let_symbols;
  std::vector<Object*> let_values;

  // skip to the next token
  token.reset(tokenizer.next());
  while (token->getType() == TokenType::OPEN_PAREN) {
    // parse the current binding symbol
    token.reset(tokenizer.next());
    check(token.get(), TokenType::SYMBOL);
    let_symbols.push_back(token->getSymbol());

    // parse the current binding value
    let_values.push_back(parseExpr());

    // check the current binding final ')'
    token.reset(tokenizer.next());
    check(token.get(), TokenType::CLOSE_PAREN);

    // skip to the next token
    token.reset(tokenizer.next());
  }

  // check the bindings list final ')'
  check(token.get(), TokenType::CLOSE_PAREN);

  // parse the body of the LET expression
  Object *body = parseExpr();

  // check the final ')'
  token.reset(tokenizer.next());
  check(token.get(), TokenType::CLOSE_PAREN);

  // create the lambda with the LET body and the LET symbols
  Lambda *let_lambda = allocator.createLambda(body, let_symbols);

  // return the application of the LET values to the LET lambda
  resetContext();
  return allocator.createList(let_lambda, Utils::vec2list(let_values));
}

Object* Parser::parseDefine() throw (Errors::CompileError) {
  setContext("DEFINE");

  std::unique_ptr<Token> token(tokenizer.next());
  std::vector<std::string> params;
  std::string name;
  bool isFunction = true;
  bool catch_rest_flag = false;

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

      // get the next token
      token.reset(tokenizer.next());

      // exit if the "catch rest" argument has been parsed
      if (catch_rest_flag)
        break;

      // check if there is a "catch rest" argument 
      if (token->getType() == TokenType::DOT) {
        catch_rest_flag = true;
        token.reset(tokenizer.next());
      }
    }

    if (isFirst)
      throw Errors::CompileError("Malformed DEFINE arguments, missing SYMBOL", token->getSourceCodePosition());
    else
      check(token.get(), TokenType::CLOSE_PAREN);
  } else {
    check(token.get(), TokenType::SYMBOL);
    isFunction = false;
    name = token->getSymbol();
  } 

  // parse the define expressions
  std::vector<Object*> expressions;
  token.reset(tokenizer.next());
  while (token->getType() != TokenType::CLOSE_PAREN) {
    // check that there is a valid expr
    checkExpr(token.get(), TokenType::CLOSE_PAREN);

    // store the expr
    expressions.push_back(dispatch(token.get()));
    token.reset(tokenizer.next());
  }

  // check for the final paren ')'
  check(token.get(), TokenType::CLOSE_PAREN);

  // create and optimize the define body if possible
  Object* value = nullptr;
  if (expressions.size() == 0)
    throw Errors::CompileError("Malformed DEFINE body, it's empty", token->getSourceCodePosition());
  else if (expressions.size() == 1)
    value = expressions[0];
  else
    value = allocator.createSequence(expressions);

  // return the proper definition object
  resetContext();
  if (isFunction)
    return allocator.createDefine(name, allocator.createLambda(value, params, catch_rest_flag));
  else
    return allocator.createDefine(name, value);
}

Object* Parser::parseQuote(bool check_paren) throw (Errors::CompileError) {
  setContext("QUOTE");

  Object *quote = allocator.createQuote(parseExpr());

  // check for the final paren ')' if needed
  if (check_paren) {
    std::unique_ptr<Token> token(tokenizer.next());
    check(token.get(), TokenType::CLOSE_PAREN);
  }

  resetContext();
  return quote;
}

Object* Parser::parseBegin() throw (Errors::CompileError) {
  setContext("BEGIN");

  std::unique_ptr<Token> token(tokenizer.next());
  
  // parse the expressions
  std::vector<Object*> expressions;
  while (token->getType() != TokenType::CLOSE_PAREN) {
    // check that there is a valid expr
    checkExpr(token.get(), TokenType::CLOSE_PAREN);

    expressions.push_back(dispatch(token.get()));
    token.reset(tokenizer.next());
  }

  // check for the final paren ')'
  check(token.get(), TokenType::CLOSE_PAREN);

  // create and optimize the begin if possible
  Object* value = nullptr;
  if (expressions.size() == 0)
    throw Errors::CompileError("Malformed BEGIN, it's empty", token->getSourceCodePosition());
  else if (expressions.size() == 1)
    value = expressions[0];
  else
    value = allocator.createSequence(expressions);

  resetContext();
  return value;
}

Object* Parser::dispatch(Token *token) throw (Errors::CompileError) {
  switch (token->getType()) {
    case TokenType::NIL:          return allocator.createNil();
    case TokenType::SYMBOL:       return allocator.createSymbol(token->getSymbol());
    case TokenType::CHARACTER:    return allocator.createCharacter(token->getCharacter());
    case TokenType::STRING:       return allocator.createString(token->getString());
    case TokenType::INT_NUMBER:   return allocator.createIntNumber(token->getIntNumber());
    case TokenType::FLOAT_NUMBER: return allocator.createFloatNumber(token->getFloatNumber());
    case TokenType::BOOL_TRUE:    return allocator.createBoolean(true);
    case TokenType::BOOL_FALSE:   return allocator.createBoolean(false);
    case TokenType::SMART_QUOTE:  return parseQuote(false);
    case TokenType::OPEN_PAREN:   return parseList();
    case TokenType::EOS:          return nullptr;
    case TokenType::UNKNOWN:
    default:                      throw Errors::CompileError("Undefined token found", token->getSourceCodePosition());
  }
}

void Parser::check(Token *token, TokenType expected_type) throw (Errors::CompileError) {
  if (token == nullptr || token->getType() != expected_type) {
    std::stringstream buf;
    buf << "expected " << Utils::type2str(expected_type) << ", ";
    if (token != nullptr)
      buf << "found " << Utils::type2str(token->getType());
    else
      buf << "found NULL";

    throw Errors::CompileError(getContext(), buf.str(), token->getSourceCodePosition());
  }
}

void Parser::checkExpr(Token *token, TokenType suggested_type) throw (Errors::CompileError) {
  if (token == nullptr ||
      token->getType() == TokenType::EOS ||
      token->getType() == TokenType::UNKNOWN) {
    std::stringstream buf;
    buf << "expected an expression or " << Utils::type2str(suggested_type) << ", ";
    if (token != nullptr)
      buf << "found " << Utils::type2str(token->getType());
    else
      buf << "found NULL";

    throw Errors::CompileError(getContext(), buf.str(), token->getSourceCodePosition());
  }
}

void Parser::setContext(std::string&& context) {
  current_context = context;
}

void Parser::resetContext() {
  setContext("");
}

std::string& Parser::getContext() {
  return current_context;
}

}
