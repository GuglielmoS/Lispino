#include "Allocator.h"

namespace Lispino {

Allocator::Allocator(Memory& memory) : memory(memory), symbols_counter(0) {
  /* DO NOTHING */
}

Memory& Allocator::getMemory() {
  return memory;
}

Symbol* Allocator::createSymbol(std::string value) {
  Symbol *symbol = static_cast<Symbol*>(memory.allocate(ObjectType::SYMBOL));
  symbol->setValue(value);

  return symbol;
}

String* Allocator::createString(std::string value) {
  String *str = static_cast<String*>(memory.allocate(ObjectType::STRING));
  str->setValue(value);

  return str;
}

IntNumber* Allocator::createIntNumber(long int value) {
  IntNumber *num = static_cast<IntNumber*>(memory.allocate(ObjectType::INT_NUMBER));
  num->setValue(value);

  return num;
}

FloatNumber* Allocator::createFloatNumber(float value) {
  FloatNumber *num = static_cast<FloatNumber*>(memory.allocate(ObjectType::FLOAT_NUMBER));
  num->setValue(value);

  return num;
}

Boolean* Allocator::createBoolean(bool value) {
  return value ? memory.getTrueInstance() : memory.getFalseInstance();
}

List* Allocator::createList(Object* first, Object* rest) {
  List *list = static_cast<List*>(memory.allocate(ObjectType::LIST));
  list->setFirst(first);
  list->setRest(rest);

  return list;
}

Lambda* Allocator::createLambda(Object* body, std::vector<std::string>& arguments) {
  Lambda *lambda = static_cast<Lambda*>(memory.allocate(ObjectType::LAMBDA));
  lambda->setBody(body);
  lambda->setArguments(arguments);

  return lambda;
}

Closure* Allocator::createClosure(Lambda *lambda, Environment *env) {
  Closure *closure = static_cast<Closure*>(memory.allocate(ObjectType::CLOSURE));
  closure->setLambda(lambda);
  closure->setEnv(env);

  return closure;
}

Define* Allocator::createDefine(std::string name, Object* value) {
  Define *define = static_cast<Define*>(memory.allocate(ObjectType::DEFINE));
  define->setName(createSymbol(name));
  define->setValue(value);

  return define;
}

Quote* Allocator::createQuote(Object* value) {
  Quote *quote = static_cast<Quote*>(memory.allocate(ObjectType::QUOTE));
  quote->setValue(value);

  return quote;
}

Nil* Allocator::createNil() {
  return memory.getNilInstance();
}

IfExpr* Allocator::createIf(Object* condition, Object* consequent, Object* alternative) {
  IfExpr *if_expr = static_cast<IfExpr*>(memory.allocate(ObjectType::IF));
  if_expr->setCondition(condition);
  if_expr->setConsequent(consequent);
  if_expr->setAlternative(alternative);

  return if_expr;
}

Sequence* Allocator::createSequence(std::vector<Object*>& expressions) {
  Sequence *seq = static_cast<Sequence*>(memory.allocate(ObjectType::SEQUENCE));
  seq->setValue(expressions);

  return seq;
}

}
