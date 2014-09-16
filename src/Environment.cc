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

void Environment::setParent(Environment *env) {
  this->parent = env;
}

Environment* Environment::getParent() {
  return parent;
}

Environment* Environment::extend() {
  Environment *extended_environment = new Environment();

  // since the new environment is an extension of the current one,
  // I set its parent to the current environment itself
  extended_environment->setParent(this);

  return extended_environment;
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
  throw Errors::RuntimeError(/*"Environment lookup failed with key: " + key->toString()*/);
}

BuiltinsTable Environment::initializeBuiltinFunctions() {
  BuiltinsTable bindings;

  // environment
  bindings["set!"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::Set());

  // list
  bindings["car"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::Car());
  bindings["cdr"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::Cdr());
  bindings["cons"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::Cons());

  // maths
  bindings["+"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::Add());
  bindings["-"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::Sub());
  bindings["*"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::Mul());
  bindings["/"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::Div());
  bindings["remainder"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::Remainder());

  // equality
  bindings["eq?"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::Equal());
  bindings[">"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::GreaterThan());
  bindings[">="] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::GreaterEqualThan());
  bindings["<"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::LowerThan());
  bindings["<="] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::LowerEqualThan());

  // I/O utils
  bindings["display"] = std::unique_ptr<Builtins::BuiltinFunction>(new Builtins::Display());

  return bindings;
}

}
