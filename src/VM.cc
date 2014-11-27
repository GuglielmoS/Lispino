#include "VM.h"

namespace Lispino {

// singleton instance
VM VM::instance;

Object* eval(Object *expr) {
  return VM::getEvaluator().eval(expr);
}

Object* eval(Object *expr, std::shared_ptr<Environment> env) {
  return VM::getEvaluator().eval(expr, env);
}

VM::VM()
    : global_env(std::make_shared<Environment>()),
      memory(gc),
      allocator(memory),
      gc(global_env),
      evaluator(global_env) {
  /* DO NOTHING */
}

std::shared_ptr<Environment> VM::getGlobalEnv() {
  return instance.global_env;
}

Allocator& VM::getAllocator() {
  return instance.allocator;
}

Memory& VM::getMemory() {
  return instance.memory;
}

Evaluator& VM::getEvaluator() {
  return instance.evaluator;
}
}
