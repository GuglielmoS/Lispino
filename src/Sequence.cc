#include "Sequence.h"

#include "VM.h"

namespace Lispino {

void Sequence::setValue(std::vector<Object*> value) {
  this->expressions = value;
}

std::vector<Object*>& Sequence::getValue() {
  return expressions;
}

std::string Sequence::toString() const {
  return "SEQUENCE";
}

}
