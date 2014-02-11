// Internal headers
#include "../src/Parser.h"
#include "../src/Object.h"
#include "../src/Nil.h"
#include "../src/Symbol.h"
#include "../src/String.h"
#include "../src/IntNumber.h"
#include "../src/FloatNumber.h"
#include "../src/List.h"
#include "../src/Lambda.h"
#include "../src/Define.h"
#include "../src/Quote.h"

// GTest headers
#include <gtest/gtest.h>

// Standard C++ headers
#include <sstream>

using namespace Lispino;

TEST(InterpreterTests, NIL) {
    std::stringstream stream("nil");
    Parser parser(&stream);
    
    // parse the stream and check the expressions
    Object *expr(parser.parseExpr());
    ASSERT_TRUE(expr->eval()->isNil());
}

TEST(InterpreterTests, BuiltinCar) {
    std::stringstream stream("(car (QUOTE (1 2 3))) (car) (car nil)");
    Parser parser(&stream);
    
    // parse the stream and check the expressions
    Object *expr(parser.parseExpr()->eval());
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(1, static_cast<IntNumber*>(expr)->getValue());

    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isNil());

    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isNil());
}

TEST(InterpreterTests, BuiltinCdr) {
    std::stringstream stream("(cdr (QUOTE (1 2 3))) (cdr) (cdr nil)");
    Parser parser(&stream);
    
    // parse the stream and check the expressions
    Object *expr(parser.parseExpr()->eval());
    ASSERT_TRUE(expr->isList());
    ASSERT_TRUE(static_cast<List*>(expr)->getFirst()->isIntNumber());
    ASSERT_EQ(2, static_cast<IntNumber*>(static_cast<List*>(expr)->getFirst())->getValue());

    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isNil());

    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isNil());
}

TEST(InterpreterTests, BuiltinCons) {
    std::stringstream stream("(cons 1 2) (cons 1 (cons 2 nil))");
    Parser parser(&stream);

    // parse the stream and check the expressions
    Object *expr(parser.parseExpr()->eval());
    ASSERT_TRUE(expr->isList());
    ASSERT_TRUE(static_cast<List*>(expr)->getFirst()->isIntNumber());
    ASSERT_EQ(1, static_cast<IntNumber*>(static_cast<List*>(expr)->getFirst())->getValue());
    ASSERT_TRUE(static_cast<List*>(expr)->getRest()->isIntNumber());
    ASSERT_EQ(2, static_cast<IntNumber*>(static_cast<List*>(expr)->getRest())->getValue());

    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isList());
    ASSERT_TRUE(static_cast<List*>(expr)->getFirst()->isIntNumber());
    ASSERT_EQ(1, static_cast<IntNumber*>(static_cast<List*>(expr)->getFirst())->getValue());
    ASSERT_TRUE(static_cast<List*>(expr)->getRest()->isList());
    ASSERT_TRUE(static_cast<List*>(static_cast<List*>(expr)->getRest())->getFirst()->isIntNumber());
    ASSERT_EQ(2, static_cast<IntNumber*>(static_cast<List*>(static_cast<List*>(expr)->getRest())->getFirst())->getValue());
    ASSERT_TRUE(static_cast<List*>(static_cast<List*>(expr)->getRest())->getRest()->isNil());
}

TEST(InterpreterTests, BuiltinAdd) {
    std::stringstream stream("(+ 1 1) (+ 1 (+ 1 (+ 1 1))) (+ 1 0.5)");
    Parser parser(&stream);

    // parse the stream and check the expressions
    Object *expr(parser.parseExpr()->eval());
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(2, static_cast<IntNumber*>(expr)->getValue());

    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(4, static_cast<IntNumber*>(expr)->getValue());

    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isFloatNumber());
    ASSERT_FLOAT_EQ(1.5, static_cast<FloatNumber*>(expr)->getValue());
}

TEST(InterpreterTests, Environment) {
    std::stringstream stream("(define x 1) (define y 2) (define z (cons x y))");
    Parser parser(&stream);

    // parse the stream and check the expressions
    Object *expr(parser.parseExpr()->eval());

    // check 'x'
    ASSERT_TRUE(expr->isIntNumber());

    // check 'y'
    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isIntNumber());

    // check 'z'
    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isList());
    ASSERT_TRUE(static_cast<List*>(expr)->getFirst()->isIntNumber());
    ASSERT_EQ(1, static_cast<IntNumber*>(static_cast<List*>(expr)->getFirst())->getValue());
    ASSERT_TRUE(static_cast<List*>(expr)->getRest()->isIntNumber());
    ASSERT_EQ(2, static_cast<IntNumber*>(static_cast<List*>(expr)->getRest())->getValue());
}

TEST(InterpreterTests, Closure) {
    std::stringstream stream("(define (make-adder n) (lambda (x) (+ n x))) (define add-one (make-adder 1)) (define add-two (make-adder 2)) (add-one 0) (add-two 0) (add-one 0) (add-one (add-two 0))");
    Parser parser(&stream);

    // check 'make-adder'
    Object *expr(parser.parseExpr()->eval());
    ASSERT_TRUE(expr->isLambda());

    // check 'add-one'
    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isClosure());

    // check 'add-two'
    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isClosure());

    // check 'add-one' result
    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(1, static_cast<IntNumber*>(expr)->getValue());

    // check 'add-two' result
    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(2, static_cast<IntNumber*>(expr)->getValue());

    // check 'add-one' result
    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(1, static_cast<IntNumber*>(expr)->getValue());

    // check 'add-one' & 'add-two' result
    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(3, static_cast<IntNumber*>(expr)->getValue());
}