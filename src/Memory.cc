#include "Memory.h"

#include <cassert>

#include <algorithm>

#include "Character.h"
#include "Symbol.h"
#include "IntNumber.h"
#include "FloatNumber.h"
#include "List.h"
#include "String.h"
#include "Lambda.h"
#include "Closure.h"
#include "Quote.h"
#include "Define.h"
#include "IfExpr.h"
#include "Sequence.h"

namespace Lispino {

Memory::Memory(GarbageCollector& gc) : gc(gc), allocated_objects(0) {
  nil_instance = std::unique_ptr<Nil>(new Nil());
  true_instance = std::unique_ptr<Boolean>(new Boolean(true));
  false_instance = std::unique_ptr<Boolean>(new Boolean(false));
}

Nil* Memory::getNilInstance() {
  return nil_instance.get();
}

Boolean* Memory::getTrueInstance() {
  return true_instance.get();
}

Boolean* Memory::getFalseInstance() {
  return false_instance.get();
}

Object* Memory::allocate(ObjectType type) {
  Object *allocated_object = nullptr;

  switch (type) {
    case ObjectType::CHARACTER:
      allocated_object = new Character();
      break;
    case ObjectType::SYMBOL:
      allocated_object = new Symbol();
      break;
    case ObjectType::INT_NUMBER:
      allocated_object = new IntNumber();
      break;
    case ObjectType::FLOAT_NUMBER:
      allocated_object = new FloatNumber();
      break;
    case ObjectType::STRING:
      allocated_object = new String();
      break;
    case ObjectType::LIST:
      allocated_object = new List();
      break;
    case ObjectType::LAMBDA:
      allocated_object = new Lambda();
      break;
    case ObjectType::CLOSURE:
      allocated_object = new Closure();
      break;
    case ObjectType::QUOTE:
      allocated_object = new Quote();
      break;
    case ObjectType::DEFINE:
      allocated_object = new Define();
      break;
    case ObjectType::IF:
      allocated_object = new IfExpr();
      break;
    case ObjectType::SEQUENCE:
      allocated_object = new Sequence();
      break;
    default:
      assert(false);
  }

  // add the allocated object to the memory linked list
  memory.push_back(std::unique_ptr<Object>(allocated_object));

  // increase the counter
  allocated_objects++;

  return allocated_object;
}

size_t Memory::getAllocatedObjects() const {
  return allocated_objects;
}

size_t Memory::cleanup() {
  gc.collect();
  return releaseUnusedObjects();
}

size_t Memory::releaseUnusedObjects() {
  auto original_memory_size = memory.size();

  // remove all the objects that are not marked
  memory.erase(
    std::remove_if(
      memory.begin(),
      memory.end(),
      [&](const std::unique_ptr<Object>& object) {
        return !object->isMarked();
      }),
    memory.end());

  // return the number of objects removed
  return original_memory_size - memory.size();
}

}
