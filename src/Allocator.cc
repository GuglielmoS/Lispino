#include "Allocator.h"

namespace Lispino {
    Allocator::Allocator(Memory& memory) : memory(memory), symbolsCounter(0) {
        /* DO NOTHING */
    }

    Memory& Allocator::getMemory() {
        return memory;
    }

    Symbol* Allocator::createSymbol(std::string value) {
        Symbol *symbol = static_cast<Symbol*>(memory.allocate(Object::SYMBOL));
        symbol->setValue(value);

        return symbol;
    }

    Symbol* Allocator::createRandomSymbol() {
        Symbol *symbol = static_cast<Symbol*>(memory.allocate(Object::SYMBOL));
        symbol->setValue("SYMBOL#" + symbolsCounter);
        symbolsCounter++;

        return symbol;
    }

    String* Allocator::createString(std::string value) {
        String *str = static_cast<String*>(memory.allocate(Object::STRING));
        str->setValue(value);

        return str;
    }

    IntNumber* Allocator::createIntNumber(long int value) {
        IntNumber *num = static_cast<IntNumber*>(memory.allocate(Object::INT_NUMBER));
        num->setValue(value);

        return num;
    }

    FloatNumber* Allocator::createFloatNumber(float value) {
        FloatNumber *num = static_cast<FloatNumber*>(memory.allocate(Object::FLOAT_NUMBER));
        num->setValue(value);

        return num;
    }

    Boolean* Allocator::createBoolean(bool value) {
        return value ? memory.getTrueInstance() : memory.getFalseInstance();
    }

    List* Allocator::createList(Object* first, Object* rest) {
        List *lst = static_cast<List*>(memory.allocate(Object::LIST));
        lst->setFirst(first);
        lst->setRest(rest);

        return lst;
    }

    Lambda* Allocator::createLambda(Object* body, std::vector<std::string>& arguments) {
        Lambda *lambda = static_cast<Lambda*>(memory.allocate(Object::LAMBDA));
        lambda->setBody(body);
        lambda->setArguments(arguments);

        return lambda;
    }

    Closure* Allocator::createClosure(Lambda *lambda, Environment *env) {
        Closure *closure = static_cast<Closure*>(memory.allocate(Object::CLOSURE));
        closure->setLambda(lambda);
        closure->setEnv(env);

        return closure;
    }

    Define* Allocator::createDefine(std::string name, Object* value) {
        Define *define = static_cast<Define*>(memory.allocate(Object::DEFINE));
        define->setName(createSymbol(name));
        define->setValue(value);

        return define;
    }

    Quote* Allocator::createQuote(Object* value) {
        Quote *quote = static_cast<Quote*>(memory.allocate(Object::QUOTE));
        quote->setValue(value);

        return quote;
    }

    Nil* Allocator::createNil() {
        return memory.getNilInstance();
    }

    IfExpr* Allocator::createIf(Object* condition, Object* consequent, Object* alternative) {
        IfExpr *ifObj = static_cast<IfExpr*>(memory.allocate(Object::IF));
        ifObj->setCondition(condition);
        ifObj->setConsequent(consequent);
        ifObj->setAlternative(alternative);

        return ifObj;
    }

    Sequence* Allocator::createSequence(std::vector<Object*>& expressions) {
        Sequence *seq = static_cast<Sequence*>(memory.allocate(Object::SEQUENCE));
        seq->setValue(expressions);

        return seq;
    }
}
