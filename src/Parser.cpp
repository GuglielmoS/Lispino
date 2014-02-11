#include "Parser.h"
#include "Nil.h"
#include "List.h"
#include "String.h"
#include "Symbol.h"
#include "IntNumber.h"
#include "FloatNumber.h"
#include "Lambda.h"
#include "Define.h"
#include "Quote.h"

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

    // parse the define value
    Object *value = parseExpr();

    // check for the final paren ')'
    token.reset(tokenizer.next());
    if (token->getType() != TokenType::CLOSE_PAREN)
        throw std::runtime_error("PARSER - invalid DEFINE arguments, missing ')'");

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

Object* Parser::parseList() { 
    std::unique_ptr<Token> token(tokenizer.next());
    Object *head = nullptr;
     
    // check if the current token is a reserved keyword
    switch (token->getType()) {
        case TokenType::CLOSE_PAREN: return nullptr;
        case TokenType::LAMBDA:      return parseLambda();
        case TokenType::DEFINE:      return parseDefine();
        case TokenType::QUOTE:       return parseQuote();
        default:                     head = dispatch(token.get());
    }

    // parse the tail if needed
    Object *result = nullptr;
    token.reset(tokenizer.next());
    switch (token->getType()) {
        case TokenType::OPEN_PAREN:
            result = allocator.createList(head, allocator.createList(parseList(), nullptr));
            break;
        case TokenType::CLOSE_PAREN:
            return allocator.createList(head, nullptr);
        case TokenType::DOT:
            result = allocator.createList(head, parseExpr());
            break;
        default: 
            return allocator.createList(head, allocator.createList(dispatch(token.get()), parseList()));
    }

    // check for the final paren ')'
    token.reset(tokenizer.next());
    if (token->getType() != TokenType::CLOSE_PAREN)
        throw std::runtime_error("PARSER - invalid LIST arguments, missing ')'");

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
        case TokenType::OPEN_PAREN:   return parseList();
        default:                      return nullptr;
    }
}

Object* Parser::parseExpr() {
    std::unique_ptr<Token> token(tokenizer.next());
    return dispatch(token.get());
}

std::vector<Object*>* Parser::parse() {
    Object *currentExpr = nullptr;
    std::vector<Object*> *expressions = new std::vector<Object*>();

    while ((currentExpr = parseExpr()) != nullptr) {
        expressions->push_back(currentExpr);
    }

    return expressions;
}
