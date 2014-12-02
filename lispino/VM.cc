#include "VM.h"

#include "builtins/Set.h"
#include "builtins/SetCar.h"
#include "builtins/SetCdr.h"

#include "builtins/Car.h"
#include "builtins/Cdr.h"
#include "builtins/Cons.h"

#include "builtins/Add.h"
#include "builtins/Sub.h"
#include "builtins/Mul.h"
#include "builtins/Div.h"
#include "builtins/Remainder.h"

#include "builtins/Load.h"
#include "builtins/Display.h"

#include "builtins/Read.h"
#include "builtins/Apply.h"

#include "builtins/NumberPred.h"
#include "builtins/BooleanPred.h"
#include "builtins/PairPred.h"
#include "builtins/SymbolPred.h"
#include "builtins/CharPred.h"
#include "builtins/StringPred.h"
#include "builtins/ProcedurePred.h"
#include "builtins/ListPred.h"
#include "builtins/PromisePred.h"

#include "builtins/And.h"
#include "builtins/Or.h"

#include "builtins/Error.h"

#include "builtins/Eq.h"
#include "builtins/Eqv.h"
#include "builtins/Equal.h"

#include "builtins/NumberEqual.h"
#include "builtins/GreaterThan.h"
#include "builtins/GreaterEqualThan.h"
#include "builtins/LowerThan.h"
#include "builtins/LowerEqualThan.h"

#include "builtins/Delay.h"
#include "builtins/Force.h"
#include "builtins/LazyCons.h"

namespace lispino {

// singleton instance
VM VM::instance;

Object* eval(Object *expr) {
  return VM::getEvaluator().eval(expr);
}

Object* eval(Object *expr, std::shared_ptr<Environment> env) {
  return VM::getEvaluator().eval(expr, env);
}

void VM::bind(builtins::BuiltinFunction *fun) {
  Symbol *fun_name = getAllocator().createSymbol(fun->getName());
  getMemory().registerBuiltinFunction(fun);
  global_env->put(fun_name, fun);
}

VM::VM()
    : global_env(std::make_shared<Environment>()),
      memory(gc),
      allocator(memory),
      gc(global_env),
      evaluator(global_env) {
  
  /* 
   * Add the builtin functions to the global environment
   */

  // set functions
  bind(new builtins::Set());
  bind(new builtins::SetCar());
  bind(new builtins::SetCdr());

  // evaluation
  bind(new builtins::Read());
  bind(new builtins::Apply());

  // boolean
  bind(new builtins::And());
  bind(new builtins::Or());

  // list
  bind(new builtins::Car());
  bind(new builtins::Cdr());
  bind(new builtins::Cons());

  // maths
  bind(new builtins::Add());
  bind(new builtins::Sub());
  bind(new builtins::Mul());
  bind(new builtins::Div());
  bind(new builtins::Remainder());

  // equality
  bind(new builtins::Eq());
  bind(new builtins::Eqv());
  bind(new builtins::Equal());
  bind(new builtins::NumberEqual());
  bind(new builtins::GreaterThan());
  bind(new builtins::GreaterEqualThan());
  bind(new builtins::LowerThan());
  bind(new builtins::LowerEqualThan());

  // identity predicates
  bind(new builtins::NumberPred());
  bind(new builtins::BooleanPred());
  bind(new builtins::PairPred());
  bind(new builtins::SymbolPred());
  bind(new builtins::CharPred());
  bind(new builtins::StringPred());
  bind(new builtins::ProcedurePred());
  bind(new builtins::ListPred());
  bind(new builtins::PromisePred());

  // I/O utils
  bind(new builtins::Display());
  bind(new builtins::Load());

  // execution control
  bind(new builtins::Error());

  // lazy evaluation
  bind(new builtins::Delay());
  bind(new builtins::Force());
  bind(new builtins::LazyCons());
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
