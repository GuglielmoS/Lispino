#ifndef LISPINO_ALLOCATOR_H_
#define LISPINO_ALLOCATOR_H_

#include <unordered_map>

#include "Memory.h"
#include "Environment.h"

#include "Symbol.h"
#include "String.h"
#include "IntNumber.h"
#include "FloatNumber.h"
#include "List.h"
#include "Lambda.h"
#include "Closure.h"
#include "Define.h"
#include "Quote.h"
#include "IfExpr.h"
#include "Nil.h"
#include "Sequence.h"

namespace Lispino {

class Allocator {
 public:
  Allocator(Memory& memory);

  Memory& getMemory();

  Symbol* createSymbol(std::string value);

  String* createString(std::string value);

  IntNumber* createIntNumber(long int value);

  FloatNumber* createFloatNumber(float value);

  Boolean* createBoolean(bool value);

  List* createList(Object* first, Object* rest);

  Lambda* createLambda(Object* body, std::vector<std::string>& arguments);

  Closure* createClosure(Lambda *lambda, std::shared_ptr<Environment> env);

  Define* createDefine(std::string name, Object* value);

  Quote* createQuote(Object* value);

  Nil* createNil();

  IfExpr* createIf(Object* condition, Object* consequent, Object* alternative);

  Sequence* createSequence(std::vector<Object*>& expressions);

 private:
  // memory used for the allocated objects
  Memory &memory;

  // cache used for the symbols
  std::unordered_map<std::string, Symbol*> symbols_cache;

  bool isSymbolCached(std::string& value) const;
};

}

#endif // LISPINO_ALLOCATOR_H_
