#include "Sequence.h"

#include "VM.h"

namespace Lispino {

void Sequence::setValue(std::vector<Object*> value) {
  this->expressions = value;
}

std::vector<Object*>& Sequence::getValue() {
  return expressions;
}

Object* Sequence::eval(Environment* env) {
  Object *result = VM::getAllocator().createNil();
  for (auto& expr : expressions)
    result = expr->eval(env);

  return result;
}

void Sequence::mark() {
  Object::mark();
  for (auto& expr : expressions)
    expr->mark();
}

bool Sequence::isSequence() const {
  return true;
}

std::string Sequence::toString() const {
  return "SEQUENCE";
}

}
