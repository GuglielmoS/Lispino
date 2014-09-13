// Internal headers
#include "../src/Tokenizer.h"

// GTest headers
#include <gtest/gtest.h>

// Standard C++ headers
#include <sstream>
#include <memory>

using namespace Lispino;

TEST(TokenizerTests, SkipSpaces) {
    std::stringstream stream;

    // add some text keywords to the input stream
    stream << "    \t \t  \n  " << std::endl << " te\tst \n";

    // create the tokenizer
    Tokenizer tokenizer(stream);

    // check the presence of the two symbols (te,st)
    std::unique_ptr<Token> token(tokenizer.next()); 
    ASSERT_EQ(TokenType::SYMBOL, token->getType());
    ASSERT_EQ("te", token->getSymbol());
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::SYMBOL, token->getType());
    ASSERT_EQ("st", token->getSymbol());

    // check the End Of Stream (EOS)
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::EOS, token->getType());
}

TEST(TokenizerTests, SkipCommentsAndSpaces) {
    std::stringstream stream;

    // add some text keywords to the input stream
    stream << ";; comment 1\n;; comment ;; 2" << std::endl << " te\tst \n";

    // create the tokenizer
    Tokenizer tokenizer(stream);

    // check the presence of the two symbols (te,st)
    std::unique_ptr<Token> token(tokenizer.next()); 
    ASSERT_EQ(TokenType::SYMBOL, token->getType());
    ASSERT_EQ("te", token->getSymbol());
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::SYMBOL, token->getType());
    ASSERT_EQ("st", token->getSymbol());

    // check the End Of Stream (EOS)
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::EOS, token->getType());
}

TEST(TokenizerTests, Delimiters) {
     std::stringstream stream;

    // add some text to the input stream
    stream << "().'";

    // create the tokenizer
    Tokenizer tokenizer(stream);

    // check the presence of the delimiters
    std::unique_ptr<Token> token(tokenizer.next()); 
    ASSERT_EQ(TokenType::OPEN_PAREN, token->getType());
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::CLOSE_PAREN, token->getType());
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::DOT, token->getType());
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::SMART_QUOTE, token->getType());

    // check the End Of Stream (EOS)
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::EOS, token->getType());   
}

TEST(TokenizerTests, Symbols) {
    std::stringstream stream;

    // add some text to the input stream
    stream << "abc123 de_boh this-is-a-symbol";

    // create the tokenizer
    Tokenizer tokenizer(stream);

    // check the presence of the symbols
    std::unique_ptr<Token> token(tokenizer.next()); 
    ASSERT_EQ(TokenType::SYMBOL, token->getType());
    ASSERT_EQ("abc123", token->getSymbol());

    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::SYMBOL, token->getType());
    ASSERT_EQ("de_boh", token->getSymbol());

    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::SYMBOL, token->getType());
    ASSERT_EQ("this-is-a-symbol", token->getSymbol());

    // check the End Of Stream (EOS)
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::EOS, token->getType());
}

TEST(TokenizerTests, IntNumbers) {
    std::stringstream stream;

    // add some text to the input stream
    stream << "12345 54321 -1";

    // create the tokenizer
    Tokenizer tokenizer(stream);

    // check the presence of the numbers
    std::unique_ptr<Token> token(tokenizer.next()); 
    ASSERT_EQ(TokenType::INT_NUMBER, token->getType());
    ASSERT_EQ(12345, token->getIntNumber());
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::INT_NUMBER, token->getType());
    ASSERT_EQ(54321, token->getIntNumber());
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::INT_NUMBER, token->getType());
    ASSERT_EQ(-1, token->getIntNumber());

    // check the End Of Stream (EOS)
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::EOS, token->getType());
}

TEST(TokenizerTests, FloatNumbers) {
    std::stringstream stream;

    // add some text to the input stream
    stream << "1.5 0.1 15.0001";

    // create the tokenizer
    Tokenizer tokenizer(stream);

    // check the presence of the numbers
    std::unique_ptr<Token> token(tokenizer.next()); 
    ASSERT_EQ(TokenType::FLOAT_NUMBER, token->getType());
    ASSERT_FLOAT_EQ(1.5f, token->getFloatNumber());
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::FLOAT_NUMBER, token->getType());
    ASSERT_FLOAT_EQ(0.1f, token->getFloatNumber());
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::FLOAT_NUMBER, token->getType());
    ASSERT_FLOAT_EQ(15.0001f, token->getFloatNumber());

    // check the End Of Stream (EOS)
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::EOS, token->getType());
}

TEST(TokenizerTests, Strings) {
    std::stringstream stream;

    // add some text to the input stream
    stream << "\"Plain string\" \"String with \\\"escape\\\"\"";

    // create the tokenizer
    Tokenizer tokenizer(stream);

    // check the presence of the symbols
    std::unique_ptr<Token> token(tokenizer.next()); 
    ASSERT_EQ(TokenType::STRING, token->getType());
    ASSERT_EQ("Plain string", token->getString());

    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::STRING, token->getType());
    ASSERT_EQ("String with \"escape\"", token->getString());

    // check the End Of Stream (EOS)
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::EOS, token->getType());
}

TEST(TokenizerTests, ReservedKeywords) {
    std::stringstream stream;

    // add some reserved keywords to the input stream
    stream << "DefInE define DEFine" << std::endl;
    stream << "Nil NIL NiL nil" << std::endl;
    stream << "LamBdA LAMBDA lambda" << std::endl;
    stream << "QuoTE qUote quote" << std::endl;
    stream << "IF iF if If" << std::endl;
    stream << "true TrUe false FalSE";

    // create the tokenizer
    Tokenizer tokenizer(stream);

    // check the DEFINE keyword
    std::unique_ptr<Token> token(tokenizer.next()); 
    ASSERT_EQ(TokenType::DEFINE, token->getType());
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::DEFINE, token->getType());
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::DEFINE, token->getType());

    // check the NIL keyword
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::NIL, token->getType());
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::NIL, token->getType());
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::NIL, token->getType());
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::NIL, token->getType());

    // check the LAMBDA keyword
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::LAMBDA, token->getType());
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::LAMBDA, token->getType());
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::LAMBDA, token->getType());

    // check the QUOTE keyword
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::QUOTE, token->getType());
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::QUOTE, token->getType());
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::QUOTE, token->getType());

    // check the IF keyword
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::IF, token->getType());
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::IF, token->getType());
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::IF, token->getType());
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::IF, token->getType());

    // check the BOOLEAN keywords
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::BOOL_TRUE, token->getType());
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::BOOL_TRUE, token->getType());
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::BOOL_FALSE, token->getType());
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::BOOL_FALSE, token->getType());

    // check the End Of Stream (EOS)
    token.reset(tokenizer.next());
    ASSERT_EQ(TokenType::EOS, token->getType());
}
