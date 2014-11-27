#ifndef LISPINO_ALLOCATOR_H_
#define LISPINO_ALLOCATOR_H_

#include <unordered_map>
#include <cstdint>

#include "Memory.h"
#include "Environment.h"

#include "Symbol.h"
#include "Character.h"
#include "String.h"
#include "IntNumber.h"
#include "FloatNumber.h"
#include "List.h"
#include "Lambda.h"
#include "Closure.h"
#include "Promise.h"
#include "Define.h"
#include "Quote.h"
#include "IfExpr.h"
#include "Nil.h"
#include "Sequence.h"

namespace Lispino {

class Allocator {
 public:
  explicit Allocator(Memory& memory);

  Memory& getMemory();

  Symbol* createSymbol(std::string value);

  Character* createCharacter(char value);

  String* createString(std::string value);

  IntNumber* createIntNumber(std::int32_t value);

  FloatNumber* createFloatNumber(float value);

  Boolean* createBoolean(bool value);

  List* createList(Object* first, Object* rest);

  Lambda* createLambda(Object* body, std::vector<std::string>& arguments, bool catch_rest_flag = false);

  Closure* createClosure(Lambda* lambda, std::shared_ptr<Environment> env);

  Promise* createPromise(Object* body, std::shared_ptr<Environment> env);

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
