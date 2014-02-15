#ifndef __PARSER_H__
#define __PARSER_H__

// Internal headers
#include "VM.h"
#include "Object.h"
#include "Tokenizer.h"

// Standard C++ headers
#include <iostream>

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

#endif // __PARSER_H__
