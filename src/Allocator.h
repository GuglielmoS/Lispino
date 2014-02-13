#ifndef __ALLOCATOR_H__
#define __ALLOCATOR_H__

#include "Environment.h"
#include "Memory.h"
#include "Object.h"
#include "Symbol.h"
#include "IntNumber.h"
#include "FloatNumber.h"
#include "Boolean.h"
#include "List.h"
#include "String.h"
#include "Lambda.h"
#include "Closure.h"
#include "IfExpr.h"

namespace Lispino {

    class Allocator {
        
        // memory used for the allocated objects
        Memory &memory;

        public:

            Allocator(Memory& memory) : memory(memory) {}

            Memory& getMemory() {
                return memory;
            }

            inline Symbol* createSymbol(std::string value) {
                Symbol *symbol = static_cast<Symbol*>(memory.allocate(Object::SYMBOL));
                symbol->setValue(value);

                return symbol;
            }

            inline String* createString(std::string value) {
                String *str = static_cast<String*>(memory.allocate(Object::STRING));
                str->setValue(value);

                return str;
            }

            inline IntNumber* createIntNumber(long int value) {
                IntNumber *num = static_cast<IntNumber*>(memory.allocate(Object::INT_NUMBER));
                num->setValue(value);

                return num;
            }

            inline FloatNumber* createFloatNumber(float value) {
                FloatNumber *num = static_cast<FloatNumber*>(memory.allocate(Object::FLOAT_NUMBER));
                num->setValue(value);

                return num;
            }

            inline Boolean* createBoolean(bool value) {
                Boolean *boolean = static_cast<Boolean*>(memory.allocate(Object::BOOLEAN));
                boolean->setValue(value);

                return boolean;
            }

            inline List* createList(Object* first, Object* rest) {
                List *lst = static_cast<List*>(memory.allocate(Object::LIST));
                lst->setFirst(first);
                lst->setRest(rest);

                return lst;
            }

            inline Lambda* createLambda(Object* body, std::vector<std::string>& arguments) {
                Lambda *lambda = static_cast<Lambda*>(memory.allocate(Object::LAMBDA));
                lambda->setBody(body);
                lambda->setArguments(arguments);
                
                return lambda;
            }

            inline Closure* createClosure(Lambda *lambda, Environment *env) {
                Closure *closure = static_cast<Closure*>(memory.allocate(Object::CLOSURE));
                closure->setLambda(lambda);
                closure->setEnv(env);

                return closure;
            }

            inline Define* createDefine(std::string name, Object* value) {
                Define *define = static_cast<Define*>(memory.allocate(Object::DEFINE));
                define->setName(createSymbol(name));
                define->setValue(value);

                return define;
            }

            inline Quote* createQuote(Object* value) {
                Quote *quote = static_cast<Quote*>(memory.allocate(Object::QUOTE));
                quote->setValue(value);

                return quote;
            }

            inline Nil* createNil() {
                return static_cast<Nil*>(memory.allocate(Object::NIL));
            }

            inline IfExpr* createIf(Object* condition, Object* consequent, Object* alternative) {
                IfExpr *ifObj = static_cast<IfExpr*>(memory.allocate(Object::IF));
                ifObj->setCondition(condition);
                ifObj->setConsequent(consequent);
                ifObj->setAlternative(alternative);
                    
                return ifObj;
            }

    };
};

#endif // __ALLOCATOR_H__
