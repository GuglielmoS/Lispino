#include "Environment.h"

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

// initialize the builtin functions
BuiltinsTable Environment::builtin_functions = Environment::initializeBuiltinFunctions();

Environment::Environment() : parent(nullptr) {
  /* DO NOTHING */
}

void Environment::setParent(std::shared_ptr<Environment> env) {
  this->parent = env;
}

std::shared_ptr<Environment> Environment::getParent() const {
  return parent;
}

LookupTable& Environment::getLookupTable() {
  return frame;
}

Object* Environment::update(Symbol* key, Object* value) throw(errors::RuntimeError) {
  auto iter = frame.find(key->getValue());

  if (iter == frame.end()) {
    if (parent != nullptr) {
      parent->update(key, value);
    } else {
      throw errors::RuntimeError("Environment update failed: key = " + key->toString());
    }
  } else {
    frame[key->getValue()] = std::make_pair(key, value);
  }

  return value;
}

Object* Environment::put(Symbol* key, Object* value) {
  frame[key->getValue()] = std::make_pair(key, value);

  return value;
}

Object* Environment::get(Symbol* key) throw(errors::RuntimeError) {
  // check for builtin functions
  auto bf_iter = builtin_functions.find(key->getValue());
  if (bf_iter != builtin_functions.end())
    return bf_iter->second.get();

  // check for environment values
  auto env_iter = frame.find(key->getValue());
  if (env_iter != frame.end())
    return (env_iter->second).second;

  // check in the parent environment
  if (parent != nullptr)
    return parent->get(key);

  // the lookup has failed, thus signal an error
  throw errors::RuntimeError("Environment lookup failed: key = " + key->getValue());
}

void Environment::applyArgs(Args& arguments) {
  // retrieve the formal arguments
  auto formal_arguments = arguments.getArguments();

  // retrieve the arguments names
  auto arguments_names = arguments.getArgumentsNames();

  // add the normal arguments to the extended environment
  for (size_t i = 0; i < formal_arguments.size(); i++)
    put(arguments_names[i], formal_arguments[i]);

  // add the "catch rest" argument if needed
  if (arguments.hasCatchRest()) {
    auto last_arg = arguments_names.size()-1;
    put(arguments_names[last_arg], arguments.getCatchRest());
  }
}

std::shared_ptr<Environment> Environment::extend(std::shared_ptr<Environment> env) {
  auto extended_environment = std::make_shared<Environment>();

  // since the new environment is an extension of the current one,
  // I set its parent to the current environment itself
  extended_environment->setParent(env);

  return extended_environment;
}

void Environment::bind(BuiltinsTable& bindings, builtins::BuiltinFunction *fun) {
  bindings[fun->getName()] = std::unique_ptr<builtins::BuiltinFunction>(fun);
}

BuiltinsTable Environment::initializeBuiltinFunctions() {
  BuiltinsTable table;

  // set functions
  bind(table, new builtins::Set());
  bind(table, new builtins::SetCar());
  bind(table, new builtins::SetCdr());

  // evaluation
  bind(table, new builtins::Apply());

  // boolean
  bind(table, new builtins::And());
  bind(table, new builtins::Or());

  // list
  bind(table, new builtins::Car());
  bind(table, new builtins::Cdr());
  bind(table, new builtins::Cons());

  // maths
  bind(table, new builtins::Add());
  bind(table, new builtins::Sub());
  bind(table, new builtins::Mul());
  bind(table, new builtins::Div());
  bind(table, new builtins::Remainder());

  // equality
  bind(table, new builtins::Eq());
  bind(table, new builtins::Eqv());
  bind(table, new builtins::Equal());
  bind(table, new builtins::NumberEqual());
  bind(table, new builtins::GreaterThan());
  bind(table, new builtins::GreaterEqualThan());
  bind(table, new builtins::LowerThan());
  bind(table, new builtins::LowerEqualThan());

  // identity predicates
  bind(table, new builtins::NumberPred());
  bind(table, new builtins::BooleanPred());
  bind(table, new builtins::PairPred());
  bind(table, new builtins::SymbolPred());
  bind(table, new builtins::CharPred());
  bind(table, new builtins::StringPred());
  bind(table, new builtins::ProcedurePred());
  bind(table, new builtins::ListPred());
  bind(table, new builtins::PromisePred());

  // I/O utils
  bind(table, new builtins::Display());
  bind(table, new builtins::Load());

  // execution control
  bind(table, new builtins::Error());

  // lazy evaluation
  bind(table, new builtins::Delay());
  bind(table, new builtins::Force());
  bind(table, new builtins::LazyCons());

  return table;
}
}
