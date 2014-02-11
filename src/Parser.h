#ifndef __PARSER_H__
#define __PARSER_H__

// Internal headers
#include "Tokenizer.h"
#include "Object.h"
#include "VM.h"

// Standard C++ headers
#include <iostream>
#include <vector>

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

            Parser(std::istream* inputStream) : allocator(VM::getAllocator()), tokenizer(inputStream) {}

            Object* parseExpr();
            std::vector<Object*>* parse();

    };
};

#endif // __PARSER_H__
