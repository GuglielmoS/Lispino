#ifndef LISPINO_MEMORY_H_
#define LISPINO_MEMORY_H_

#include <iostream>
#include <memory>
#include <vector>

#include "Object.h"
#include "Nil.h"
#include "Boolean.h"
#include "GarbageCollector.h"

namespace lispino {

class Memory {
 public:
  explicit Memory(GarbageCollector& gc);

  Nil* getNilInstance();

  Boolean* getTrueInstance();

  Boolean* getFalseInstance();

  Object* allocate(ObjectType type);

  size_t cleanup();

 private:
  // reference to the garbage collector
  GarbageCollector &gc;

  // pointer to the first object in memory
  std::vector<std::unique_ptr<Object>> memory;

  // instance of frequently used objects that don't change their value
  std::unique_ptr<Nil> nil_instance;
  std::unique_ptr<Boolean> true_instance;
  std::unique_ptr<Boolean> false_instance;

  // remove the unused objects and return the number of objects deleted
  size_t releaseUnusedObjects();
};
}

#endif  // LISPINO_MEMORY_H_
