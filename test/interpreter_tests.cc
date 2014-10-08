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
#include "../src/VM.h"

// GTest headers
#include <gtest/gtest.h>

// Standard C++ headers
#include <sstream>

using namespace Lispino;

TEST(InterpreterTests, NIL) {
    std::stringstream stream("nil");
    Parser parser(stream);
    
    // parse the stream and check the expressions
    Object *expr(parser.parseExpr());
    ASSERT_TRUE(eval(expr)->isNil());
}

TEST(InterpreterTests, IfExpr) {
    std::stringstream stream("(if #t 0 1) (if #f 0 1)");
    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(0, static_cast<IntNumber*>(expr)->getValue());
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(1, static_cast<IntNumber*>(expr)->getValue());
}

TEST(InterpreterTests, BuiltinCar) {
    std::stringstream stream("(car (QUOTE (1 2 3))) (car nil)");
    Parser parser(stream);
    
    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(1, static_cast<IntNumber*>(expr)->getValue());
}

TEST(InterpreterTests, BuiltinCdr) {
    std::stringstream stream("(cdr (QUOTE (1 2 3)))");
    Parser parser(stream);
    
    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isList());
    ASSERT_TRUE(static_cast<List*>(expr)->getFirst()->isIntNumber());
    ASSERT_EQ(2, static_cast<IntNumber*>(static_cast<List*>(expr)->getFirst())->getValue());
}

TEST(InterpreterTests, BuiltinCons) {
    std::stringstream stream("(cons 1 2) (cons 1 (cons 2 nil))");
    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isList());
    ASSERT_TRUE(static_cast<List*>(expr)->getFirst()->isIntNumber());
    ASSERT_EQ(1, static_cast<IntNumber*>(static_cast<List*>(expr)->getFirst())->getValue());
    ASSERT_TRUE(static_cast<List*>(expr)->getRest()->isIntNumber());
    ASSERT_EQ(2, static_cast<IntNumber*>(static_cast<List*>(expr)->getRest())->getValue());

    expr = eval(parser.parseExpr());
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
    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(2, static_cast<IntNumber*>(expr)->getValue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(4, static_cast<IntNumber*>(expr)->getValue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFloatNumber());
    ASSERT_FLOAT_EQ(1.5, static_cast<FloatNumber*>(expr)->getValue());
}

TEST(InterpreterTests, BuiltinSub) {
    std::stringstream stream("(- 1 1) (- 1 (- 1 (- 1 1))) (- 1 0.5)");
    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(0, static_cast<IntNumber*>(expr)->getValue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(0, static_cast<IntNumber*>(expr)->getValue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFloatNumber());
    ASSERT_EQ(0.5, static_cast<FloatNumber*>(expr)->getValue());
}

TEST(InterpreterTests, BuiltinMul) {
    std::stringstream stream("(* 0 1) (* 1 (* 2 (* 3 4))) (* 1 0.5)");
    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(0, static_cast<IntNumber*>(expr)->getValue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(24, static_cast<IntNumber*>(expr)->getValue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFloatNumber());
    ASSERT_FLOAT_EQ(0.5, static_cast<FloatNumber*>(expr)->getValue());
}

TEST(InterpreterTests, BuiltinDiv) {
    std::stringstream stream("(/ 0 1) (/ 1 2) (/ 4 2) (/ 1 0) (/ 1.0 0.0) (/ 1.0 0) (/ 0 0)");
    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(0, static_cast<IntNumber*>(expr)->getValue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(0, static_cast<IntNumber*>(expr)->getValue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(2, static_cast<IntNumber*>(expr)->getValue());

    // Division by zero exception

    // (/ 1 0)
    ASSERT_THROW(eval(parser.parseExpr()), Errors::RuntimeError);

    // (/ 1.0 0.0)
    ASSERT_THROW(eval(parser.parseExpr()), Errors::RuntimeError);

    // (/ 1.0 0)
    ASSERT_THROW(eval(parser.parseExpr()), Errors::RuntimeError);

    // (/ 1 0.0)
    ASSERT_THROW(eval(parser.parseExpr()), Errors::RuntimeError);
}

TEST(InterpreterTests, BuiltinRemainder) {
    std::stringstream stream("(remainder 1 2) (remainder 5 2) (remainder 4 2)");
    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(1, static_cast<IntNumber*>(expr)->getValue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(1, static_cast<IntNumber*>(expr)->getValue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(0, static_cast<IntNumber*>(expr)->getValue());
}

TEST(InterpreterTests, BuiltinDisplay) {
    std::stringstream stream("(display 1 2 3) (display \"(+ 1 1) = \" (+ 1 1))");
    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isString());
    ASSERT_EQ("123", static_cast<String*>(expr)->getValue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isString());
    ASSERT_EQ("(+ 1 1) = 2", static_cast<String*>(expr)->getValue());
}

TEST(InterpreterTests, Environment) {
    std::stringstream stream("(define x 1) (define y 2) (define z (cons x y)) (define (sum . values) (apply + values)) (sum 1 2 3)");
    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));

    // check 'x'
    ASSERT_TRUE(expr->isIntNumber());

    // check 'y'
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isIntNumber());

    // check 'z'
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isList());
    ASSERT_TRUE(static_cast<List*>(expr)->getFirst()->isIntNumber());
    ASSERT_EQ(1, static_cast<IntNumber*>(static_cast<List*>(expr)->getFirst())->getValue());
    ASSERT_TRUE(static_cast<List*>(expr)->getRest()->isIntNumber());
    ASSERT_EQ(2, static_cast<IntNumber*>(static_cast<List*>(expr)->getRest())->getValue());

    // parse the define with the catch rest argument
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isLambda());
    ASSERT_TRUE(static_cast<Lambda*>(expr)->hasCatchRest());

    // parse the execution of the defined lambda
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(6, static_cast<IntNumber*>(expr)->getValue());
}

TEST(InterpreterTests, Closure) {
    std::stringstream stream("(define (make-adder n) (lambda (x) (+ n x))) (define add-one (make-adder 1)) (define add-two (make-adder 2)) (add-one 0) (add-two 0) (add-one 0) (add-one (add-two 0))");
    Parser parser(stream);

    // check 'make-adder'
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isLambda());

    // check 'add-one'
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isClosure());

    // check 'add-two'
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isClosure());

    // check 'add-one' result
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(1, static_cast<IntNumber*>(expr)->getValue());

    // check 'add-two' result
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(2, static_cast<IntNumber*>(expr)->getValue());

    // check 'add-one' result
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(1, static_cast<IntNumber*>(expr)->getValue());

    // check 'add-one' & 'add-two' result
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(3, static_cast<IntNumber*>(expr)->getValue());
}

TEST(InterpreterTests, BuiltinNumberEqual) {
    std::stringstream stream("(= 0 0) (= 0 1) (= 2 2) (= 0.5 0.5)");
    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isTrue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());
}

TEST(InterpreterTests, BuiltinGreaterThan) {
    std::stringstream stream("(> 0 0) (> 0 1) (> 1 0) (> 2.1 2) (> 2.1 1.9) (> 1 0.5)");
    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isFalse());
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());
}

TEST(InterpreterTests, BuiltinGreaterEqualThan) {
    std::stringstream stream("(>= 0 0) (>= 0 1) (>= 1 0) (>= 2.1 2) (>= 2.1 1.9) (>= 1 0.5)");
    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isTrue());
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());
}

TEST(InterpreterTests, BuiltinLowerThan) {
    std::stringstream stream("(< 0 0) (< 1 0) (< 0 1) (< 2 2.1) (< 1.9 2.1) (< 0.5 1)");
    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isFalse());
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());
}

TEST(InterpreterTests, BuiltinLowerEqualThan) {
    std::stringstream stream("(<= 0 0) (<= 1 0) (<= 0 1) (<= 2 2.1) (<= 1.9 2.1) (<= 0.5 1)");
    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isTrue());
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());
}

TEST(InterpreterTests, BuiltinApply) {
    std::stringstream stream("(apply + '(1 2 3 4 5 6 7 8 9 10))");
    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isIntNumber());
    ASSERT_EQ(55, static_cast<IntNumber*>(expr)->getValue());
}

TEST(InterpreterTests, BuiltinNumberPred) {
    std::stringstream stream("(number? 1) (number? 1.5) (number? nil) (number? #\\a) (number? \"ciao\")");
    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isTrue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());
}

TEST(InterpreterTests, BuiltinCharPred) {
    std::stringstream stream("(char? #\\a) (char? #\\A) (char? nil) (char? 1) (char? 1.5) (char? \"ciao\")");
    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isTrue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());
}

TEST(InterpreterTests, BuiltinSymbolPred) {
    std::stringstream stream("(symbol? 'x) (symbol? nil) (symbol? 1) (symbol? 1.5) (symbol? \"ciao\")");
    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isTrue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());
}

TEST(InterpreterTests, BuiltinBooleanPred) {
    std::stringstream stream("(boolean? #t) (boolean? #f) (boolean? #T) (boolean? #F) (boolean? 'x) (boolean? nil) (boolean? 1) (boolean? 1.5) (boolean? \"ciao\")");
    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isTrue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());
}

TEST(InterpreterTests, BuiltinStringPred) {
    std::stringstream stream("(string? \"ciao\") (string? #t) (string? #f) (string? 'x) (string? nil) (string? 1) (string? 1.5)");

    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isTrue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());
}

TEST(InterpreterTests, BuiltinPairPred) {
    std::stringstream stream("(pair? '(1 . 2)) (pair? '(1 2)) (pair? \"ciao\") (pair? #t) (pair? #f) (pair? 'x) (pair? nil) (pair? 1) (pair? 1.5)");

    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isTrue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());
}

TEST(InterpreterTests, BuiltinProcedurePred) {
    std::stringstream stream("(procedure? (lambda (x) x)) (procedure? ((lambda (x) (lambda (y) y)) 1)) (procedure? nil) (procedure? #t) (procedure? 'x)");

    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isTrue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());
}

TEST(InterpreterTests, BuiltinListPred) {
    std::stringstream stream("(list? '(1 . 2)) (list? '(1 2)) (list? \"ciao\") (list? #t) (list? #f) (list? 'x) (list? nil) (list? 1) (list? 1.5)");

    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());
}

TEST(InterpreterTests, BuiltinPromisePred) {
    std::stringstream stream("(promise? (delay 1)) (promise? (cdr (lazy-cons 1 2))) (promise? '(1 . 2)) (promise? '(1 2)) (promise? \"ciao\") (promise? #t) (promise? #f) (promise? 'x) (promise? nil) (promise? 1) (promise? 1.5)");

    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));
    ASSERT_TRUE(expr->isBoolean());
    ASSERT_TRUE(expr->isTrue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());
}

TEST(InterpreterTests, BuiltinError) {
    std::stringstream stream("(error \"this is an error\")");

    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(parser.parseExpr());
    ASSERT_THROW(eval(expr), Errors::RuntimeError);
}

TEST(InterpreterTests, BuiltinEq) {
    std::stringstream stream("(eq? 'x 'x) (eq? 'x 'y) (eq? #\\a #\\a) (eq? 1 1) (eq? 2.5 2.5) (eq? \"a\" \"a\")");

    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));

    // (eq? 'x 'x)
    ASSERT_TRUE(expr->isTrue());

    // (eq? 'x 'y)
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    // (eq? #\a #\a)
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    // (eq? 1 1)
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    // (eq? 2.5 2.5)
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    // (eq? "a" "a")
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());
}

TEST(InterpreterTests, BuiltinEqv) {
    std::stringstream stream("(eqv? 'x 'x) (eqv? #\\a #\\a) (eqv? 1 1) (eqv? 2.5 2.5) (eqv? '(1) '(1)) (eqv? \"a\" \"a\")");

    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));

    // (eqv? 'x 'x)
    ASSERT_TRUE(expr->isTrue());

    // (eqv? #\a #\a)
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());

    // (eqv? 1 1)
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());

    // (eqv? 2.5 2.5)
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());

    // (eqv? '(1) '(1))
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());

    // (eq? "a" "a")
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isFalse());
}

TEST(InterpreterTests, BuiltinEqual) {
    std::stringstream stream("(equal? '(1 2 3) '(1 2 3)) (equal? \"a\" \"a\") (equal? 'x 'x) (equal? 1 1)");

    Parser parser(stream);

    // parse the stream and check the expressions
    Object *expr(eval(parser.parseExpr()));

    // (eqv? '(1 2 3) '(1 2 3))
    ASSERT_TRUE(expr->isTrue());

    // (eqv? "a" "a")
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());

    // (eqv? 1 1)
    expr = eval(parser.parseExpr());
    ASSERT_TRUE(expr->isTrue());
}
