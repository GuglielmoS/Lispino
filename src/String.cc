#include "String.h"

namespace Lispino {

String::String() : value("") {
  /* DO NOTHING */
}

String::String(std::string value) : value(value) {
  /* DO NOTHING */
}

void String::setValue(std::string value) {
  this->value = value;
}

std::string String::getValue() const {
  return value;
}

Object* String::eval(Environment&) {
  return this;
}

int String::compare(Object* obj) {
  if (this == obj)
    return 0;
  else
    return obj->compareString(this);
}

int String::compareString(String* obj) {
  return obj->getValue().compare(value);
}

bool String::isAtom() const {
  return true;
}

bool String::isString() const {
  return true;
}

std::string String::toString() const {
  std::stringstream buf;
  buf << "\"" << value << "\"";
  return buf.str();
}

}
