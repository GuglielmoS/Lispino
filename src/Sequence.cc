#include "Sequence.h"

#include "VM.h"

namespace Lispino {

void Sequence::setValue(std::vector<Object*> value) {
  this->expressions = value;
}

std::vector<Object*>& Sequence::getValue() {
  return expressions;
}

void Sequence::mark() {
  Object::mark();
  for (auto& expr : expressions)
    expr->mark();
}

std::string Sequence::toString() const {
  return "SEQUENCE";
}

}
