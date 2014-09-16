#include "IntNumber.h"
#include "FloatNumber.h"
#include "VM.h"

namespace Lispino {

IntNumber::IntNumber() : value(0) {
  /* DO NOTHING */
}

IntNumber::IntNumber(std::int64_t value) : value(value) {
  /* DO NOTHING */
}

void IntNumber::setValue(std::int64_t value) {
  this->value = value;
}

std::int64_t IntNumber::getValue() const {
  return value;
}

Object* IntNumber::eval(Environment*) throw (Errors::RuntimeError) {
  return this;
}

int IntNumber::compare(const Object* obj) const {
  if (obj == this)
    return 0;
  else
    return obj->compareInt(this);
}

int IntNumber::compareInt(const IntNumber* obj) const {
  return obj->value - value;
}

int IntNumber::compareFloat(const FloatNumber* obj) const {
  double temp = obj->getValue() - value;

  if (temp > 0.0)
    return 1;
  else if (temp < 0.0)
    return -1;
  else
    return 0;
}

Object* IntNumber::negate() {
  return VM::getAllocator().createIntNumber(-value);
}

Object* IntNumber::add(Object* obj) {
  return obj->addInt(this);
}

Object* IntNumber::addInt(IntNumber* obj) {
  return VM::getAllocator().createIntNumber(value + obj->value);
}

Object* IntNumber::addFloat(FloatNumber* obj) {
  return VM::getAllocator().createIntNumber(value + obj->getValue());
}

Object* IntNumber::sub(Object* obj) {
  return obj->subInt(this);
}

Object* IntNumber::subInt(IntNumber* obj) {
  return VM::getAllocator().createIntNumber(obj->value - value);
}

Object* IntNumber::subFloat(FloatNumber* obj) {
  return VM::getAllocator().createFloatNumber(obj->getValue() - value);
}

Object* IntNumber::mul(Object* obj) {
  return obj->mulInt(this);
}

Object* IntNumber::mulInt(IntNumber* obj) {
  return VM::getAllocator().createIntNumber(obj->value * value);
}

Object* IntNumber::mulFloat(FloatNumber* obj) {
  return VM::getAllocator().createFloatNumber(obj->getValue() * value);
}

Object* IntNumber::div(Object* obj) {
  return obj->divInt(this);
}

Object* IntNumber::divInt(IntNumber* obj) {
  return VM::getAllocator().createIntNumber(obj->value / value);
}

Object* IntNumber::divFloat(FloatNumber* obj) {
  return VM::getAllocator().createFloatNumber(obj->getValue() / value);
}

Object* IntNumber::remainder(Object* obj) {
  return obj->remainderInt(this);
}

Object* IntNumber::remainderInt(IntNumber* obj) {
  return VM::getAllocator().createIntNumber(obj->value % value);
}

bool IntNumber::isAtom() const {
  return true;
}

bool IntNumber::isIntNumber() const {
  return true;
}

std::string IntNumber::toString() const {
  std::stringstream buf;
  buf << value;
  return buf.str();
}

}
