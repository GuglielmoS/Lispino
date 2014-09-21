#include "Lambda.h"

#include "VM.h"

namespace Lispino {

Lambda::Lambda() : Object(ObjectType::LAMBDA), body(nullptr) {
  /* DO NOTHING */
}

Lambda::Lambda(Object* body, std::vector<std::string> arguments)
    : Object(ObjectType::LAMBDA), body(body), arguments(arguments) {
  /* DO NOTHING */
}

void Lambda::setBody(Object* body) {
  this->body = body;
}

void Lambda::setArguments(std::vector<std::string> arguments) {
  this->arguments = arguments;
}

Object* Lambda::getBody() {
  return body;
}

std::vector<std::string> Lambda::getArguments() {
  return arguments;
}

Object* Lambda::eval(Environment* env) throw (Errors::RuntimeError) {
  return VM::getAllocator().createClosure(this, std::shared_ptr<Environment>(env));
}

Object* Lambda::apply(std::vector<Object*>& actual_args, Environment* env) throw (Errors::RuntimeError) {
  if (arguments.size() != actual_args.size())
    throw Errors::RuntimeError("Invalid function call: wrong number of arguments");

  // extend the current environment with the arguments to apply
  Environment *extended_env = env->extend(std::make_shared<Environment>()).get();
  for (unsigned int i = 0; i < arguments.size(); i++)
    extended_env->put(VM::getAllocator().createSymbol(arguments[i]), actual_args[i]);

  // evaluate the code associated to this lambda in the extended environment
  Object *result = body->eval(extended_env);

  // delete the environment if not needed: if we have a closure as result, it
  // must not be deleted because it is now part of the closure
  if (!result->isClosure())
    delete extended_env;

  return result;
}

void Lambda::mark() {
  Object::mark();
  body->mark();
}

bool Lambda::isLambda() const {
  return true;
}

std::string Lambda::toString() const {
  return "LAMBDA";
}

}
