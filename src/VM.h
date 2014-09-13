#ifndef LISPINO_VM_H_
#define LISPINO_VM_H_

#include "Memory.h"
#include "Allocator.h"
#include "GarbageCollector.h"
#include "Environment.h"

namespace Lispino {

class VM {
 public:
  static Environment& getGlobalEnv();
  static Allocator& getAllocator();
  static Memory& getMemory();

 private:
  VM();

  // memory used at runtime by the objects
  Memory memory;

  // used when at runtime when a new object is needed 
  Allocator allocator;

  // gc used by the memory when needed
  GarbageCollector gc;

  // environment that contains the global definitions 
  Environment globalEnv;

  // singleton instance
  static VM instance;
};

}

#endif // LISPINO_VM_H_
