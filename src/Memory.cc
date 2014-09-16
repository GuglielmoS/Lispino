#include "Memory.h"

#include <cassert>

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

Memory::Memory(GarbageCollector& gc) 
    : gc(gc), first(nullptr), allocated_objects(0) {
  nil_instance = std::unique_ptr<Nil>(new Nil());
  true_instance = std::unique_ptr<Boolean>(new Boolean(true));
  false_instance = std::unique_ptr<Boolean>(new Boolean(false));
}

Memory::~Memory() {
  // delete the objects stored in the virtual memory
  MemoryNode *current = first;
  while (current != nullptr) {
    MemoryNode *temp = current;
    current = current->next;
    delete temp;
  }
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
  MemoryNode *newNode = new MemoryNode{std::unique_ptr<Object>(allocated_object), first};
  first = newNode;

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

// remove the unused objects and return the number of objects deleted
size_t Memory::releaseUnusedObjects() {
  MemoryNode *current = first;
  MemoryNode *prev = nullptr;
  size_t released_objects = 0;

  while (current != nullptr) {
    // if the current object is not marked, then it is not visibile
    // and it must be removed from the memory
    if (!current->object->isMarked()) {
      // if we have the first node
      if (prev == nullptr) {
        first = current->next;
        delete current;
        current = first;
      } else {
        prev->next = current->next;
        delete current;
        current = prev->next;
      }

      // increase the counter for statistics
      released_objects++;

      // decrease the number of allocated objects
      allocated_objects--;
    } else {
      // unmark the current object and skip to the next
      current->object->unmark();
      prev = current;
      current = current->next;
    }
  }

  return released_objects;
}

}
