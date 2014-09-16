#ifndef LISPINO_MEMORY_H_
#define LISPINO_MEMORY_H_

#include <iostream>
#include <memory>

#include "Object.h"
#include "Nil.h"
#include "Boolean.h"
#include "GarbageCollector.h"

namespace Lispino {

class Memory {
 public:

  Memory(GarbageCollector& gc);

  ~Memory();

  Nil* getNilInstance();

  Boolean* getTrueInstance();

  Boolean* getFalseInstance();

  Object* allocate(ObjectType type);

  size_t getAllocatedObjects() const;

  size_t cleanup();

 private:
  // This struct contains a pointer to an allocated object and the pointer
  // to the next element in memory
  struct MemoryNode {
    std::unique_ptr<Object> object;
    MemoryNode *next;
  };

  // reference to the garbage collector
  GarbageCollector &gc;

  // pointer to the first object in memory
  MemoryNode *first;

  // instance of frequently used objects that don't change their value
  Nil *nil_instance;
  Boolean *true_instance;
  Boolean *false_instance;

  // number of objects stored
  size_t allocated_objects;

  // remove the unused objects and return the number of objects deleted
  size_t releaseUnusedObjects();
};

}

#endif // LISPINO_MEMORY_H_
