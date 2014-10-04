#include "Environment.h"

#include "builtins/Set.h"

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

namespace Lispino {

// initialize the builtin functions
BuiltinsTable Environment::builtin_functions = Environment::initializeBuiltinFunctions();

Environment::Environment() : parent(nullptr) {
  /* DO NOTHING */
}

void Environment::setParent(std::shared_ptr<Environment> env) {
  this->parent = env;
}

std::shared_ptr<Environment> Environment::getParent() {
  return parent;
}

LookupTable& Environment::getLookupTable() {
  return frame;
}

Object* Environment::update(Symbol* key, Object* value) throw (Errors::RuntimeError) {
  auto iter = frame.find(key->getValue());

  if (iter == frame.end()) {
    if (parent != nullptr) {
      parent->update(key, value);
    } else {
      throw Errors::RuntimeError(/*"Environment update failed with key: " + key->toString()*/);
    }
  } else {
    frame[key->getValue()] = std::make_pair(key,value);
  }

  return value;
}

Object* Environment::put(Symbol* key, Object* value) {
  frame[key->getValue()] = std::make_pair(key,value);

  return value;
}

Object* Environment::get(Symbol* key) throw (Errors::RuntimeError) {
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
  throw Errors::RuntimeError("Environment lookup failed: key = " + key->getValue());
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

void Environment::bind(BuiltinsTable& bindings, Builtins::BuiltinFunction *fun) {
  bindings[fun->getName()] = std::unique_ptr<Builtins::BuiltinFunction>(fun);
}

BuiltinsTable Environment::initializeBuiltinFunctions() {
  BuiltinsTable table;

  // environment
  bind(table, new Builtins::Set());

  // evaluation
  bind(table, new Builtins::Apply());

  // boolean
  bind(table, new Builtins::And());
  bind(table, new Builtins::Or());

  // list
  bind(table, new Builtins::Car());
  bind(table, new Builtins::Cdr());
  bind(table, new Builtins::Cons());

  // maths
  bind(table, new Builtins::Add());
  bind(table, new Builtins::Sub());
  bind(table, new Builtins::Mul());
  bind(table, new Builtins::Div());
  bind(table, new Builtins::Remainder());

  // equality
  bind(table, new Builtins::Eq());
  bind(table, new Builtins::Eqv());
  bind(table, new Builtins::Equal());
  bind(table, new Builtins::NumberEqual());
  bind(table, new Builtins::GreaterThan());
  bind(table, new Builtins::GreaterEqualThan());
  bind(table, new Builtins::LowerThan());
  bind(table, new Builtins::LowerEqualThan());

  // identity predicates
  bind(table, new Builtins::NumberPred());
  bind(table, new Builtins::BooleanPred());
  bind(table, new Builtins::PairPred());
  bind(table, new Builtins::SymbolPred());
  bind(table, new Builtins::CharPred());
  bind(table, new Builtins::StringPred());
  bind(table, new Builtins::ProcedurePred());
  bind(table, new Builtins::ListPred());
  bind(table, new Builtins::PromisePred());

  // I/O utils
  bind(table, new Builtins::Display());
  bind(table, new Builtins::Load());

  // execution control
  bind(table, new Builtins::Error());

  // lazy evaluation
  bind(table, new Builtins::Delay());
  bind(table, new Builtins::Force());
  bind(table, new Builtins::LazyCons());

  return table;
}

}
