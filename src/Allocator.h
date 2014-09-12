#ifndef LISPINO_ALLOCATOR_H_
#define LISPINO_ALLOCATOR_H_

#include "Memory.h"
#include "Environment.h"

namespace Lispino {

    class Allocator {
        public:

            Allocator(Memory& memory);

            Memory& getMemory();

            Symbol* createSymbol(std::string value);
            Symbol* createRandomSymbol();
            String* createString(std::string value);
            IntNumber* createIntNumber(long int value);
            FloatNumber* createFloatNumber(float value);
            Boolean* createBoolean(bool value);
            List* createList(Object* first, Object* rest);
            Lambda* createLambda(Object* body, std::vector<std::string>& arguments);
            Closure* createClosure(Lambda *lambda, Environment *env);
            Define* createDefine(std::string name, Object* value);
            Quote* createQuote(Object* value);
            Nil* createNil();
            IfExpr* createIf(Object* condition, Object* consequent, Object* alternative);
            Sequence* createSequence(std::vector<Object*>& expressions);

        private:

            // memory used for the allocated objects
            Memory& memory;

            // counter used to generate random symbols
            int symbolsCounter;
    };
};

#endif // LISPINO_ALLOCATOR_H_
