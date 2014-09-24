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

bool String::equal(const Object* obj) const {
  return obj->equalString(this);
}

bool String::equalString(const String* obj) const {
  return value == obj->value;
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

std::string String::toString() const {
  std::stringstream buf;
  buf << "\"" << escape(value) << "\"";
  return buf.str();
}

std::string String::escape(std::string str) const {
  std::stringstream buf;

  for (const auto& ch : str) {
    switch (ch) {
      case '\n':
        buf << "\\n";
        break;
      case '\\':
        buf << "\\";
        break;
      case '\"':
        buf << "\\\"";
        break;
      default:
        buf << ch;
    }
  }

  return buf.str();
}

}
