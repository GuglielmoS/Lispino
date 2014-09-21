#include "String.h"

namespace Lispino {

String::String() : Object(ObjectType::STRING), value("") {
  /* DO NOTHING */
}

String::String(std::string value) : Object(ObjectType::STRING), value(value) {
  /* DO NOTHING */
}

void String::setValue(std::string value) {
  this->value = value;
}

std::string String::getValue() const {
  return value;
}

Object* String::eval(Environment*) throw (Errors::RuntimeError) {
  return this;
}

int String::compare(const Object* obj) const throw (Errors::RuntimeError) {
  if (this == obj)
    return 0;
  else
    return obj->compareString(this);
}

int String::compareString(const String* obj) const throw (Errors::RuntimeError) {
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
