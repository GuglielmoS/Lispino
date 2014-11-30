#include "Environment.h"

namespace lispino {

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
}
