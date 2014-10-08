#ifndef LISPINO_VM_H_
#define LISPINO_VM_H_

#include <memory>

#include "Memory.h"
#include "Allocator.h"
#include "GarbageCollector.h"
#include "Environment.h"
#include "Evaluator.h"

namespace Lispino {

Object* eval(Object *expr);
Object* eval(Object *expr, std::shared_ptr<Environment> env);

class VM {
 public:
  static std::shared_ptr<Environment> getGlobalEnv();
  static Evaluator& getEvaluator();
  static Allocator& getAllocator();
  static Memory& getMemory();

 private:
  VM();

  // environment that contains the global definitions 
  std::shared_ptr<Environment> global_env;

  // memory used at runtime by the objects
  Memory memory;

  // used when at runtime when a new object is needed 
  Allocator allocator;

  // gc used by the memory when needed
  GarbageCollector gc;

  // the evaluator to use for evaluating expressions
  Evaluator evaluator;

  // singleton instance
  static VM instance;
};

}

#endif // LISPINO_VM_H_
