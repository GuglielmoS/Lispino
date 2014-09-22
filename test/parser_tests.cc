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

TEST(ParserTests, Characters) {
    std::stringstream stream;
 
    // add some text to the input stream
    for (char ch = 'a'; ch < 'z'; ch++)
      stream << "#\\" << (char)ch << " ";
    for (char ch = 'A'; ch < 'Z'; ch++)
      stream << "#\\" << (char)ch << " ";

    Parser parser(stream);
    for (char ch = 'a'; ch < 'z'; ch++) {
      Object *expr(parser.parseExpr());
      ASSERT_TRUE(expr->isCharacter());
      ASSERT_EQ(ch, static_cast<Character*>(expr)->getValue());
    }
    for (char ch = 'A'; ch < 'Z'; ch++) {
      Object *expr(parser.parseExpr());
      ASSERT_TRUE(expr->isCharacter());
      ASSERT_EQ(ch, static_cast<Character*>(expr)->getValue());
    }
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
    std::stringstream stream("#t #T #f #F");
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

TEST(ParserTests, Let) {
    std::stringstream stream("(let ((a 0) (b (+ 1 2))) (+ a b))");
    Parser parser(stream);
    
    // parse the stream and check the expressions
    Object *expr(parser.parseExpr());

    // check that the parsed expr is a list who's first element is a lambda
    ASSERT_TRUE(expr->isList());
    List *let_list = static_cast<List*>(expr);
    ASSERT_TRUE(let_list->getFirst() != nullptr);
    ASSERT_TRUE(let_list->getFirst()->isLambda());

    // check that the lambda has the right parameters
    Lambda *lambda = static_cast<Lambda*>(let_list->getFirst());
    std::vector<std::string> params = lambda->getArguments();
    Object *body = lambda->getBody();

    // check the lambda parameters
    ASSERT_EQ(2, params.size());
    ASSERT_EQ("a", params[0]);
    ASSERT_EQ("b", params[1]);

    // check the lambda body
    ASSERT_TRUE(body->isList());
    List *temp = static_cast<List*>(body);
    ASSERT_TRUE(temp->getFirst()->isSymbol());
    ASSERT_EQ("+", static_cast<Symbol*>(temp->getFirst())->getValue());
    ASSERT_TRUE(temp->getRest()->isList());
    temp = static_cast<List*>(temp->getRest());
    ASSERT_TRUE(temp->getFirst()->isSymbol());
    ASSERT_EQ("a", static_cast<Symbol*>(temp->getFirst())->getValue());
    ASSERT_TRUE(temp->getRest()->isList());
    temp = static_cast<List*>(temp->getRest());
    ASSERT_TRUE(temp->getFirst()->isSymbol());
    ASSERT_EQ("b", static_cast<Symbol*>(temp->getFirst())->getValue());

    // check that the arguments provided to the lambda are correct
    temp = static_cast<List*>(let_list->getRest());
    ASSERT_TRUE(temp->getFirst()->isIntNumber());
    ASSERT_EQ(0, static_cast<IntNumber*>(temp->getFirst())->getValue());
    ASSERT_TRUE(temp->getRest()->isList());
    temp = static_cast<List*>(temp->getRest());
    ASSERT_TRUE(temp->getFirst()->isList());
    temp = static_cast<List*>(temp->getFirst());
    ASSERT_TRUE(temp->getFirst()->isSymbol());
    ASSERT_EQ("+", static_cast<Symbol*>(temp->getFirst())->getValue());
    ASSERT_TRUE(temp->getRest()->isList());
    temp = static_cast<List*>(temp->getRest());
    ASSERT_TRUE(temp->getFirst()->isIntNumber());
    ASSERT_EQ(1, static_cast<IntNumber*>(temp->getFirst())->getValue());
    ASSERT_TRUE(temp->getRest()->isList());
    temp = static_cast<List*>(temp->getRest());
    ASSERT_TRUE(temp->getFirst()->isIntNumber());
    ASSERT_EQ(2, static_cast<IntNumber*>(temp->getFirst())->getValue());
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
    std::stringstream stream("(quote a) 'a '(1 2 3)");
    Parser parser(stream);
    
    // parse the stream and check the expressions
    Object *expr(parser.parseExpr());

    ASSERT_TRUE(expr->isQuote());
    Quote *quote = static_cast<Quote*>(expr);
    ASSERT_TRUE(quote->getValue()->isSymbol());
    ASSERT_EQ("a", static_cast<Symbol*>(quote->getValue())->getValue());

    expr = parser.parseExpr();
    ASSERT_TRUE(expr->isQuote());
    quote = static_cast<Quote*>(expr);
    ASSERT_TRUE(quote->getValue()->isSymbol());
    ASSERT_EQ("a", static_cast<Symbol*>(quote->getValue())->getValue());

    expr = parser.parseExpr();
    ASSERT_TRUE(expr->isQuote());
    quote = static_cast<Quote*>(expr);
    ASSERT_TRUE(quote->getValue()->isList());
    List *lst = static_cast<List*>(quote->getValue());
    ASSERT_TRUE(lst->getFirst()->isIntNumber());
    ASSERT_EQ(1, static_cast<IntNumber*>(lst->getFirst())->getValue());
    ASSERT_TRUE(lst->getRest()->isList());
    lst = static_cast<List*>(lst->getRest());
    ASSERT_TRUE(lst->getFirst()->isIntNumber());
    ASSERT_EQ(2, static_cast<IntNumber*>(lst->getFirst())->getValue());
    ASSERT_TRUE(lst->getRest()->isList());
    lst = static_cast<List*>(lst->getRest());
    ASSERT_TRUE(lst->getFirst()->isIntNumber());
    ASSERT_EQ(3, static_cast<IntNumber*>(lst->getFirst())->getValue());
    ASSERT_TRUE(lst->getRest()->isNil());
}

TEST(ParserTests, IfExpr) {
    std::stringstream stream("(if #t 0 1)");
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

TEST(ParserTests, CondExpr) {
    std::stringstream stream("(cond ((< x 0) (- x)) (otherwise x))");
    Parser parser(stream);
    
    // parse the stream and check the expressions
    Object *expr(parser.parseExpr());

    ASSERT_TRUE(expr->isIfExpr());
    IfExpr *if_obj = static_cast<IfExpr*>(expr);
    
    /*
     * Check the first IF
     */
  
    // check the condition expr
    ASSERT_TRUE(if_obj->getCondition()->isList());
    List *cond_list = static_cast<List*>(if_obj->getCondition());
    ASSERT_TRUE(cond_list->getFirst()->isSymbol());
    ASSERT_EQ("<", static_cast<Symbol*>(cond_list->getFirst())->getValue());

    ASSERT_TRUE(cond_list->getRest()->isList());
    cond_list = static_cast<List*>(cond_list->getRest());
    ASSERT_TRUE(cond_list->getFirst()->isSymbol());
    ASSERT_EQ("x", static_cast<Symbol*>(cond_list->getFirst())->getValue());

    ASSERT_TRUE(cond_list->getRest()->isList());
    cond_list = static_cast<List*>(cond_list->getRest());
    ASSERT_TRUE(cond_list->getFirst()->isIntNumber());
    ASSERT_EQ(0, static_cast<IntNumber*>(cond_list->getFirst())->getValue());

    ASSERT_TRUE(cond_list->getRest()->isNil());

    // check the consequent expr
    ASSERT_TRUE(if_obj->getConsequent()->isList());
    List *conseq_list = static_cast<List*>(if_obj->getConsequent());
    ASSERT_TRUE(conseq_list->getFirst()->isSymbol());
    ASSERT_EQ("-", static_cast<Symbol*>(conseq_list->getFirst())->getValue());

    ASSERT_TRUE(conseq_list->getRest()->isList());
    conseq_list = static_cast<List*>(conseq_list->getRest());
    ASSERT_TRUE(conseq_list->getFirst()->isSymbol());
    ASSERT_EQ("x", static_cast<Symbol*>(conseq_list->getFirst())->getValue());

    ASSERT_TRUE(conseq_list->getRest()->isNil());

    /*
     * check the alternative IF
     */

    ASSERT_TRUE(if_obj->getAlternative()->isIfExpr());
    if_obj = static_cast<IfExpr*>(if_obj->getAlternative());
    ASSERT_TRUE(if_obj->getCondition()->isSymbol());
    ASSERT_EQ("otherwise", static_cast<Symbol*>(if_obj->getCondition())->getValue());
    ASSERT_TRUE(if_obj->getConsequent()->isSymbol());
    ASSERT_EQ("x", static_cast<Symbol*>(if_obj->getConsequent())->getValue());
    ASSERT_TRUE(if_obj->getAlternative()->isNil());
}

TEST(ParserTests, BeginExpr) {
    std::stringstream stream("(begin 0 x (+ 1 2)) (begin x)");
    Parser parser(stream);
    
    // parse the stream and check the expressions
    Object *expr(parser.parseExpr());

    /*
     * Check the first begin.
     */

    // check the sequence's expressions
    ASSERT_TRUE(expr->isSequence());
    Sequence *seq = static_cast<Sequence*>(expr);
    std::vector<Object*>& expressions = seq->getValue(); 
    ASSERT_EQ(3, expressions.size());

    // check the first expr
    ASSERT_TRUE(expressions[0]->isIntNumber());
    ASSERT_EQ(0, static_cast<IntNumber*>(expressions[0])->getValue());

    // check the second expr
    ASSERT_TRUE(expressions[1]->isSymbol());
    ASSERT_EQ("x", static_cast<Symbol*>(expressions[1])->getValue());

    // check the third and last expr
    ASSERT_TRUE(expressions[2]->isList());
    List *list = static_cast<List*>(expressions[2]);
    ASSERT_TRUE(list->getFirst()->isSymbol());
    ASSERT_EQ("+", static_cast<Symbol*>(list->getFirst())->getValue());
    ASSERT_TRUE(list->getRest()->isList());
    list = static_cast<List*>(list->getRest());
    ASSERT_TRUE(list->getFirst()->isIntNumber());
    ASSERT_EQ(1, static_cast<IntNumber*>(list->getFirst())->getValue());
    ASSERT_TRUE(list->getRest()->isList());
    list = static_cast<List*>(list->getRest());
    ASSERT_TRUE(list->getFirst()->isIntNumber());
    ASSERT_EQ(2, static_cast<IntNumber*>(list->getFirst())->getValue());
    ASSERT_TRUE(list->getRest()->isNil());

    /*
     * Check the second begin.
     * Since it is a BEGIN with only one expression, it must be optimized to that
     * single expression.
     */

    expr = parser.parseExpr(); 
    ASSERT_TRUE(expr->isSymbol());
    ASSERT_EQ("x", static_cast<Symbol*>(expr)->getValue());
}
