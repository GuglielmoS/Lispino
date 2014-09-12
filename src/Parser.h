#ifndef LISPINO_PARSER_H_
#define LISPINO_PARSER_H_

#include <iostream>

#include "VM.h"
#include "Object.h"
#include "Tokenizer.h"

namespace Lispino {

    class Parser {
       
        Allocator &allocator;
        Tokenizer tokenizer;

        Object* parseIf();
        Object* parseList();
        Object* parseLambda();
        Object* parseDefine();
        Object* parseQuote();
        Object* dispatch(Token *token);

        public:

            Parser(std::istream& inputStream) : allocator(VM::getAllocator()), tokenizer(inputStream) {}

            Object* parseExpr();
            Object* parse();

    };
};

#endif // LISPINO_PARSER_H_
