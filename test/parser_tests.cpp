// Internal headers
#include "../src/Parser.h"
#include "../src/Object.h"
#include "../src/Nil.h"
#include "../src/Symbol.h"
#include "../src/String.h"
#include "../src/IntNumber.h"
#include "../src/FloatNumber.h"
#include "../src/Boolean.h"
#include "../src/List.h"
#include "../src/Lambda.h"
#include "../src/Define.h"
#include "../src/Quote.h"
#include "../src/IfExpr.h"

// GTest headers
#include <gtest/gtest.h>

// Standard C++ headers
#include <sstream>

using namespace Lispino;

TEST(ParserTests, NIL) {
    std::stringstream stream("nil");
    Parser parser(stream);
    
    // parse the stream and check the expressions
    Object *expr(parser.parseExpr());
    ASSERT_TRUE(expr->isNil());
}

TEST(ParserTests, Symbols) {
    std::stringstream stream("example-test symbol-123");
    Parser parser(stream);
    
    // parse the stream and check the expressions
    Object *expr(parser.parseExpr());

    ASSERT_TRUE(expr->isSymbol());
    Symbol *sym = static_cast<Symbol*>(expr);
    ASSERT_EQ("example-test", sym->getValue());

    expr = parser.parseExpr();
    ASSERT_TRUE(expr->isSymbol());
    sym = static_cast<Symbol*>(expr);
    ASSERT_EQ("symbol-123", sym->getValue());
}

TEST(ParserTests, IntNumbers) {
    std::stringstream stream("0 12 345 42");
    Parser parser(stream);
    
    // parse the stream and check the expressions
    Object *expr(parser.parseExpr());

    ASSERT_TRUE(expr->isIntNumber());
    IntNumber *num = static_cast<IntNumber*>(expr);
    ASSERT_EQ(0, num->getValue());

    expr = parser.parseExpr();
    ASSERT_TRUE(expr->isIntNumber());
    num = static_cast<IntNumber*>(expr);
    ASSERT_EQ(12, num->getValue());

    expr = parser.parseExpr();
    ASSERT_TRUE(expr->isIntNumber());
    num = static_cast<IntNumber*>(expr);
    ASSERT_EQ(345, num->getValue());

    expr = parser.parseExpr();
    ASSERT_TRUE(expr->isIntNumber());
    num = static_cast<IntNumber*>(expr);
    ASSERT_EQ(42, num->getValue());
}

TEST(ParserTests, FloatNumbers) {
    std::stringstream stream("0.1 42.05");
    Parser parser(stream);
    
    // parse the stream and check the expressions
    Object *expr(parser.parseExpr());

    ASSERT_TRUE(expr->isFloatNumber());
    FloatNumber *num = static_cast<FloatNumber*>(expr);
    ASSERT_FLOAT_EQ(0.1, num->getValue());

    expr = parser.parseExpr();
    ASSERT_TRUE(expr->isFloatNumber());
    num = static_cast<FloatNumber*>(expr);
    ASSERT_FLOAT_EQ(42.05, num->getValue());
}

TEST(ParserTests, Booleans) {
    std::stringstream stream("true TrUE false FalSe");
    Parser parser(stream);
    
    // parse the stream and check the expressions
    Object *expr(parser.parseExpr());
    ASSERT_TRUE(expr->isBoolean());
    ASSERT_TRUE(static_cast<Boolean*>(expr)->isTrue());
    expr = parser.parseExpr();
    ASSERT_TRUE(expr->isBoolean());
    ASSERT_TRUE(static_cast<Boolean*>(expr)->isTrue());
    expr = parser.parseExpr();
    ASSERT_TRUE(expr->isBoolean());
    ASSERT_TRUE(static_cast<Boolean*>(expr)->isFalse());
    expr = parser.parseExpr();
    ASSERT_TRUE(expr->isBoolean());
    ASSERT_TRUE(static_cast<Boolean*>(expr)->isFalse());
}

TEST(ParserTests, Strings) {
    std::stringstream stream("\"plain string\" \"string with \\\"escape\\\"\"");
    Parser parser(stream);
    
    // parse the stream and check the expressions
    Object *expr(parser.parseExpr());

    ASSERT_TRUE(expr->isString());
    String *str = static_cast<String*>(expr);
    ASSERT_EQ("plain string", str->getValue());

    expr = parser.parseExpr();
    ASSERT_TRUE(expr->isString());
    str = static_cast<String*>(expr);
    ASSERT_EQ("string with \"escape\"", str->getValue());
}

TEST(ParserTests, Lists) {
    std::stringstream stream("(1 2 3) (a . b)");
    Parser parser(stream);
    
    // parse the stream and check the expressions
    Object *expr(parser.parseExpr());

    // first element
    ASSERT_TRUE(expr->isList());
    List *lst = static_cast<List*>(expr);
    ASSERT_TRUE(lst->getFirst()->isIntNumber());
    ASSERT_EQ(1, static_cast<IntNumber*>(lst->getFirst())->getValue());

    // second element
    ASSERT_NE(lst->getRest(), nullptr);
    ASSERT_TRUE(lst->getRest()->isList());
    lst = static_cast<List*>(lst->getRest());
    ASSERT_TRUE(lst->getFirst()->isIntNumber());
    ASSERT_EQ(2, static_cast<IntNumber*>(lst->getFirst())->getValue());

    // third element
    ASSERT_NE(lst->getRest(), nullptr);
    ASSERT_TRUE(lst->getRest()->isList());
    lst = static_cast<List*>(lst->getRest());
    ASSERT_TRUE(lst->getFirst()->isIntNumber());
    ASSERT_EQ(3, static_cast<IntNumber*>(lst->getFirst())->getValue());

    // list end
    ASSERT_TRUE(lst->getRest()->isNil());

    // check the improper list
    expr = parser.parseExpr();
    ASSERT_TRUE(expr->isList());
    lst = static_cast<List*>(expr);
    ASSERT_TRUE(lst->getFirst()->isSymbol());
    ASSERT_EQ("a", static_cast<Symbol*>(lst->getFirst())->getValue());
    ASSERT_TRUE(lst->getRest()->isSymbol());
    ASSERT_EQ("b", static_cast<Symbol*>(lst->getRest())->getValue());
}

TEST(ParserTests, Lambdas) {
    std::stringstream stream("(lambda (x) (+ x x))");
    Parser parser(stream);
    
    // parse the stream and check the expressions
    Object *expr(parser.parseExpr());

    // first element
    ASSERT_TRUE(expr->isLambda());
    Lambda *lambda = static_cast<Lambda*>(expr);
    std::vector<std::string> params = lambda->getArguments();
    Object *body = lambda->getBody();

    // check the parameters
    ASSERT_EQ(1, params.size());
    ASSERT_EQ("x", params[0]);

    // check the body
    ASSERT_TRUE(body->isList());
    List *temp = static_cast<List*>(body);
    ASSERT_TRUE(temp->getFirst()->isSymbol());
    ASSERT_EQ("+", static_cast<Symbol*>(temp->getFirst())->getValue());
    ASSERT_TRUE(temp->getRest()->isList());
    temp = static_cast<List*>(temp->getRest());
    ASSERT_TRUE(temp->getFirst()->isSymbol());
    ASSERT_EQ("x", static_cast<Symbol*>(temp->getFirst())->getValue());
    ASSERT_TRUE(temp->getRest()->isList());
    temp = static_cast<List*>(temp->getRest());
    ASSERT_TRUE(temp->getFirst()->isSymbol());
    ASSERT_EQ("x", static_cast<Symbol*>(temp->getFirst())->getValue());
}

TEST(ParserTests, Defines) {
    std::stringstream stream("(define (square x) (* x x))");
    Parser parser(stream);
    
    // parse the stream and check the expressions
    Object *expr(parser.parseExpr());

    ASSERT_TRUE(expr->isDefine());
    Define *define = static_cast<Define*>(expr);
    ASSERT_EQ("square", define->getName());

    Object *value = define->getValue();
    ASSERT_TRUE(value->isLambda());
    Lambda *lambda = static_cast<Lambda*>(value);
    std::vector<std::string> params = lambda->getArguments();
    Object *body = lambda->getBody();

    // check the parameters
    ASSERT_EQ(1, params.size());
    ASSERT_EQ("x", params[0]);

    // check the body
    ASSERT_TRUE(body->isList());
    List *temp = static_cast<List*>(body);
    ASSERT_TRUE(temp->getFirst()->isSymbol());
    ASSERT_EQ("*", static_cast<Symbol*>(temp->getFirst())->getValue());
    ASSERT_TRUE(temp->getRest()->isList());
    temp = static_cast<List*>(temp->getRest());
    ASSERT_TRUE(temp->getFirst()->isSymbol());
    ASSERT_EQ("x", static_cast<Symbol*>(temp->getFirst())->getValue());
    ASSERT_TRUE(temp->getRest()->isList());
    temp = static_cast<List*>(temp->getRest());
    ASSERT_TRUE(temp->getFirst()->isSymbol());
    ASSERT_EQ("x", static_cast<Symbol*>(temp->getFirst())->getValue());
}

TEST(ParserTests, Quotes) {
    std::stringstream stream("(quote a)");
    Parser parser(stream);
    
    // parse the stream and check the expressions
    Object *expr(parser.parseExpr());

    ASSERT_TRUE(expr->isQuote());
    Quote *quote = static_cast<Quote*>(expr);
    ASSERT_TRUE(quote->getValue()->isSymbol());
    ASSERT_EQ("a", static_cast<Symbol*>(quote->getValue())->getValue());
}

TEST(ParserTests, IfExpr) {
    std::stringstream stream("(if true 0 1)");
    Parser parser(stream);
    
    // parse the stream and check the expressions
    Object *expr(parser.parseExpr());

    ASSERT_TRUE(expr->isIfExpr());
    IfExpr *ifObj = static_cast<IfExpr*>(expr);
    ASSERT_TRUE(ifObj->getCondition()->isBoolean());
    ASSERT_TRUE(static_cast<Boolean*>(ifObj->getCondition())->isTrue());
    ASSERT_TRUE(ifObj->getConsequent()->isIntNumber());
    ASSERT_EQ(0, static_cast<IntNumber*>(ifObj->getConsequent())->getValue());
    ASSERT_TRUE(ifObj->getAlternative()->isIntNumber());
    ASSERT_EQ(1, static_cast<IntNumber*>(ifObj->getAlternative())->getValue());
}
