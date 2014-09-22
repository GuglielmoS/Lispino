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
#include "builtins/Display.h"
#include "builtins/Load.h"
#include "builtins/Equal.h"
#include "builtins/GreaterThan.h"
#include "builtins/GreaterEqualThan.h"
#include "builtins/LowerThan.h"
#include "builtins/LowerEqualThan.h"

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
  bind(table, new Builtins::Equal());
  bind(table, new Builtins::GreaterThan());
  bind(table, new Builtins::GreaterEqualThan());
  bind(table, new Builtins::LowerThan());
  bind(table, new Builtins::LowerEqualThan());

  // I/O utils
  bind(table, new Builtins::Display());
  bind(table, new Builtins::Load());

  return table;
}

}
