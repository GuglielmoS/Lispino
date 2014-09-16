#include "FloatNumber.h"
#include "IntNumber.h"
#include "VM.h"

#include <cmath>

namespace Lispino {

FloatNumber::FloatNumber() : value(0.0) {
  /* DO NOTHING */
}

FloatNumber::FloatNumber(double value) : value(value) {
  /* DO NOTHING */
}

void FloatNumber::setValue(double value) {
  this->value = value;
}

double FloatNumber::getValue() const {
  return value;
}

Object* FloatNumber::eval(Environment*) throw (Errors::RuntimeError) {
  return this;
}

int FloatNumber::compare(const Object* obj) const {
  if (obj == this)
    return 0;
  else
    return obj->compareFloat(this);
}

int FloatNumber::compareInt(const IntNumber* obj) const {
  float temp = obj->getValue() - value;

  if (temp > 0.0)
    return 1;
  else if (temp < 0.0)
    return -1;
  else
    return 0;
}

int FloatNumber::compareFloat(const FloatNumber* obj) const {
  float temp = obj->value - value;

  if (temp > 0.0)
    return 1;
  else if (temp < 0.0)
    return -1;
  else
    return 0;
}

Object* FloatNumber::negate() {
  return VM::getAllocator().createFloatNumber(-value);
}

Object* FloatNumber::add(Object* obj) {
  return obj->addFloat(this);
}

Object* FloatNumber::addInt(IntNumber* obj) {
  return VM::getAllocator().createFloatNumber(value + obj->getValue());
}

Object* FloatNumber::addFloat(FloatNumber* obj) {
  return VM::getAllocator().createFloatNumber(value + obj->value);
}

Object* FloatNumber::sub(Object* obj) {
  return obj->subFloat(this);
}

Object* FloatNumber::subInt(IntNumber* obj) {
  return VM::getAllocator().createFloatNumber(obj->getValue() - value);
}

Object* FloatNumber::subFloat(FloatNumber* obj) {
  return VM::getAllocator().createFloatNumber(obj->value - value);
}

Object* FloatNumber::mul(Object* obj) {
  return obj->mulFloat(this);
}

Object* FloatNumber::mulInt(IntNumber* obj) {
  return VM::getAllocator().createFloatNumber(obj->getValue() * value);
}

Object* FloatNumber::mulFloat(FloatNumber* obj) {
  return VM::getAllocator().createFloatNumber(obj->value * value);
}

Object* FloatNumber::div(Object* obj) {
  return obj->divFloat(this);
}

Object* FloatNumber::divInt(IntNumber* obj) {
  return VM::getAllocator().createFloatNumber(obj->getValue() / value);
}

Object* FloatNumber::divFloat(FloatNumber* obj) {
  return VM::getAllocator().createFloatNumber(obj->value / value);
}

Object* FloatNumber::remainder(Object* obj) {
  return obj->remainderFloat(this);
}

Object* FloatNumber::remainderFloat(FloatNumber* obj) {
  return VM::getAllocator().createIntNumber(fmod(obj->value, value));
}

bool FloatNumber::isAtom() const {
  return true;
}

bool FloatNumber::isFloatNumber() const {
  return true;
}

std::string FloatNumber::toString() const {
  std::stringstream buf;
  buf << value;
  return buf.str();
}

}
