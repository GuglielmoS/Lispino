#include "Promise.h"

#include <sstream>

#include "VM.h"

namespace Lispino {

Promise::Promise() 
    : Object(ObjectType::PROMISE), 
      body(nullptr), 
      result(nullptr),
      cached_result_flag(false),
      env(nullptr) {
  /* DO NOTHING */
}

void Promise::setBody(Object* body) {
  this->body = body;
}

void Promise::setCachedResult(Object* result) {
  this->result = result;
  this->cached_result_flag = true;
}

void Promise::setEnv(std::shared_ptr<Environment> env) {
  this->env = env;
}

Object* Promise::getBody() {
  return body;
}

Object* Promise::getCachedResult() {
  return result;
}

std::shared_ptr<Environment> Promise::getEnv() {
  return env;
}

bool Promise::hasCachedResult() const {
  return cached_result_flag;
}

std::string Promise::toString() const {
  std::stringstream buf;
  buf << "<#PROMISE:" << this << ">";
  return buf.str();
}

}
