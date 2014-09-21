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

void Lambda::mark() {
  Object::mark();
  body->mark();
}

std::string Lambda::toString() const {
  return "LAMBDA";
}

}
