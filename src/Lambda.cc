#include "Lambda.h"

#include <sstream>

#include "VM.h"

namespace Lispino {

Lambda::Lambda() 
    : Object(ObjectType::LAMBDA),
      body(nullptr),
      catch_rest_flag(false) {
  /* DO NOTHING */
}

Lambda::Lambda(Object* body, std::vector<std::string> arguments)
    : Object(ObjectType::LAMBDA),
      body(body), 
      arguments(arguments),
      catch_rest_flag(false) {
  /* DO NOTHING */
}

void Lambda::setBody(Object* body) {
  this->body = body;
}

void Lambda::setArguments(std::vector<std::string> arguments) {
  this->arguments = arguments;
}

void Lambda::setCatchRestFlag(bool catch_rest_flag) {
  this->catch_rest_flag = catch_rest_flag;
}

Object* Lambda::getBody() {
  return body;
}

std::vector<std::string> Lambda::getArguments() const {
  return arguments;
}

std::uint32_t Lambda::getRequiredArguments() const {
  return arguments.size();
}

bool Lambda::hasCatchRest() const {
  return catch_rest_flag;
}

std::string Lambda::toString() const {
  std::stringstream buf;
  buf << "<#LAMBDA:" << this << ">";
  return buf.str();
}

}
