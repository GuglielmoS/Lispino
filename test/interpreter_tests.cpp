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

TEST(InterpreterTests, BuiltinSub) {
    std::stringstream stream("(- 1 1) (- 1 (- 1 (- 1 1))) (- 1 0.5)");
    Parser parser(&stream);

    // parse the stream and check the expressions
    Object *expr(parser.parseExpr()->eval());
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(0, static_cast<IntNumber*>(expr)->getValue());

    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(0, static_cast<IntNumber*>(expr)->getValue());

    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isFloatNumber());
    ASSERT_EQ(0.5, static_cast<FloatNumber*>(expr)->getValue());
}

TEST(InterpreterTests, BuiltinMul) {
    std::stringstream stream("(* 0 1) (* 1 (* 2 (* 3 4))) (* 1 0.5)");
    Parser parser(&stream);

    // parse the stream and check the expressions
    Object *expr(parser.parseExpr()->eval());
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(0, static_cast<IntNumber*>(expr)->getValue());

    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(24, static_cast<IntNumber*>(expr)->getValue());

    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isFloatNumber());
    ASSERT_FLOAT_EQ(0.5, static_cast<FloatNumber*>(expr)->getValue());
}

TEST(InterpreterTests, BuiltinDiv) {
    std::stringstream stream("(/ 0 1) (/ 1 2) (/ 4 2)");
    Parser parser(&stream);

    // parse the stream and check the expressions
    Object *expr(parser.parseExpr()->eval());
    ASSERT_TRUE(expr->isFloatNumber());
    ASSERT_FLOAT_EQ(0.0f, static_cast<FloatNumber*>(expr)->getValue());

    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isFloatNumber());
    ASSERT_FLOAT_EQ(0.5f, static_cast<FloatNumber*>(expr)->getValue());

    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isFloatNumber());
    ASSERT_FLOAT_EQ(2.0f, static_cast<FloatNumber*>(expr)->getValue());
}

TEST(InterpreterTests, BuiltinRemainder) {
    std::stringstream stream("(remainder 1 2) (remainder 5 2) (remainder 4 2)");
    Parser parser(&stream);

    // parse the stream and check the expressions
    Object *expr(parser.parseExpr()->eval());
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(1, static_cast<IntNumber*>(expr)->getValue());

    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(1, static_cast<IntNumber*>(expr)->getValue());

    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(0, static_cast<IntNumber*>(expr)->getValue());
}

TEST(InterpreterTests, BuiltinDisplay) {
    std::stringstream stream("(display 1 2 3) (display \"(+ 1 1) = \" (+ 1 1))");
    Parser parser(&stream);

    // parse the stream and check the expressions
    Object *expr(parser.parseExpr()->eval());
    ASSERT_TRUE(expr->isString());
    ASSERT_EQ("123", static_cast<String*>(expr)->getValue());

    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isString());
    ASSERT_EQ("(+ 1 1) = 2", static_cast<String*>(expr)->getValue());
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

TEST(InterpreterTests, BuiltinEqual) {
    std::stringstream stream("(= 0 0) (= 0 1) (= 2 2) (= 2.0 2) (= 0.5 0.5) (= 1 \"a\")");
    Parser parser(&stream);

    // parse the stream and check the expressions
    Object *expr(parser.parseExpr()->eval());
    ASSERT_TRUE(expr->isBoolean());
    ASSERT_TRUE(static_cast<Boolean*>(expr)->isTrue());
    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isBoolean());
    ASSERT_TRUE(static_cast<Boolean*>(expr)->isFalse());
    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isBoolean());
    ASSERT_TRUE(static_cast<Boolean*>(expr)->isTrue());
    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isBoolean());
    ASSERT_TRUE(static_cast<Boolean*>(expr)->isFalse());
    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isBoolean());
    ASSERT_TRUE(static_cast<Boolean*>(expr)->isTrue());
    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isBoolean());
    ASSERT_TRUE(static_cast<Boolean*>(expr)->isFalse());
}

TEST(InterpreterTests, BuiltinGreaterThan) {
    std::stringstream stream("(> 0 0) (> 0 1) (> 1 0) (> 2.1 2)");
    Parser parser(&stream);

    // parse the stream and check the expressions
    Object *expr(parser.parseExpr()->eval());
    ASSERT_TRUE(expr->isBoolean());
    ASSERT_TRUE(static_cast<Boolean*>(expr)->isFalse());
    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isBoolean());
    ASSERT_TRUE(static_cast<Boolean*>(expr)->isFalse());
    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isBoolean());
    ASSERT_TRUE(static_cast<Boolean*>(expr)->isTrue());
    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isBoolean());
    ASSERT_TRUE(static_cast<Boolean*>(expr)->isTrue());
}

TEST(InterpreterTests, IfExpr) {
    std::stringstream stream("(if true 0 1) (if false 0 1)");
    Parser parser(&stream);

    // parse the stream and check the expressions
    Object *expr(parser.parseExpr()->eval());
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(0, static_cast<IntNumber*>(expr)->getValue());
    expr = parser.parseExpr()->eval();
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(1, static_cast<IntNumber*>(expr)->getValue());
}
