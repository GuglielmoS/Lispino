#include "Memory.h"

namespace Lispino {

Memory::Memory(GarbageCollector& gc) 
    : gc(gc), first(nullptr), allocated_objects(0) {
  nil_instance = new Nil();
  true_instance = new Boolean(true);
  false_instance = new Boolean(false);
}

Memory::~Memory() {
  // delete the objects stored in the virtual memory
  MemoryNode *current = first;
  while (current != nullptr) {
    MemoryNode *temp = current;
    current = current->next;
    delete temp;
  }

  // delete the cached instances
  delete nil_instance;
  delete true_instance;
  delete false_instance;
}

Nil* Memory::getNilInstance() {
  return nil_instance;
}

Boolean* Memory::getTrueInstance() {
  return true_instance;
}

Boolean* Memory::getFalseInstance() {
  return false_instance;
}

Object* Memory::allocate(Object::ObjectType type) {
  Object *allocated_object = nullptr;

  switch (type) {
    case Object::SYMBOL:
      allocated_object = new Symbol();
      break;
    case Object::INT_NUMBER:
      allocated_object = new IntNumber();
      break;
    case Object::FLOAT_NUMBER:
      allocated_object = new FloatNumber();
      break;
    case Object::STRING:
      allocated_object = new String();
      break;
    case Object::LIST:
      allocated_object = new List();
      break;
    case Object::LAMBDA:
      allocated_object = new Lambda();
      break;
    case Object::CLOSURE:
      allocated_object = new Closure();
      break;
    case Object::QUOTE:
      allocated_object = new Quote();
      break;
    case Object::DEFINE:
      allocated_object = new Define();
      break;
    case Object::IF:
      allocated_object = new IfExpr();
      break;
    case Object::SEQUENCE:
      allocated_object = new Sequence();
      break;
    default:
      throw std::runtime_error("[MEMORY-allocate ERROR] invalid ObjectType!");
  }

  // add the allocated object to the memory linked list
  MemoryNode *newNode = new MemoryNode(allocated_object, first);
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
