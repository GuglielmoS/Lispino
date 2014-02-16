#include "Parser.h"

#include <vector>
#include <memory>

using namespace Lispino;

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
            }
            else
                params.push_back(token->getSymbol());

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
    Object *ifObj = allocator.createIf(condition, consequent, alternative);

    // check for the final paren ')'
    if (alternative != nullptr) {
        token.reset(tokenizer.next());
        if (token->getType() != TokenType::CLOSE_PAREN)
            throw std::runtime_error("PARSER - invalid IF arguments, missing ')'");
    }

    return ifObj;
}

Object* Parser::parseList() { 
    std::unique_ptr<Token> token(tokenizer.next());
    Object *head = nullptr;
     
    // check if the current token is a reserved keyword
    switch (token->getType()) {
        case TokenType::CLOSE_PAREN: return allocator.createList(allocator.createNil(), allocator.createNil());
        case TokenType::LAMBDA:      return parseLambda();
        case TokenType::DEFINE:      return parseDefine();
        case TokenType::QUOTE:       return parseQuote();
        case TokenType::IF:          return parseIf();
        default:                     head = dispatch(token.get());
    }

    // create the final list
    List *result = allocator.createList(head, allocator.createNil());
    List *current = result;
    bool improperList = false;

    // parse the tail if needed
    token.reset(tokenizer.next());
    while (token->getType() != TokenType::CLOSE_PAREN) {
        if (token->getType() == TokenType::DOT) {
            improperList = true;
            token.reset(tokenizer.next());
        }

        if (improperList) {
            current->setRest(dispatch(token.get()));
            improperList = false;
        }
        else {
            current->setRest(allocator.createList(dispatch(token.get()), allocator.createNil()));
            current = static_cast<List*>(current->getRest());
        }
        
        token.reset(tokenizer.next());
    }

    return result;
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

Object* Parser::parseExpr() {
    std::unique_ptr<Token> token(tokenizer.next());
    return dispatch(token.get());
}

Object* Parser::parse() {
    Object *expr = parseExpr();

    // check for the End Of Stream
    std::unique_ptr<Token> token(tokenizer.next());
    if (token->getType() != TokenType::EOS)
        throw std::runtime_error("PARSER - missing End Of Stream!");

    return expr;
}
