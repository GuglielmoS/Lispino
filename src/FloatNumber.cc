#include "FloatNumber.h"
#include "IntNumber.h"
#include "VM.h"

#include <cmath>

namespace Lispino {

FloatNumber::FloatNumber() : Object(ObjectType::FLOAT_NUMBER), value(0.0) {
  /* DO NOTHING */
}

FloatNumber::FloatNumber(double value) : Object(ObjectType::FLOAT_NUMBER), value(value) {
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

int FloatNumber::compare(const Object* obj) const throw (Errors::RuntimeError) {
  if (obj == this)
    return 0;
  else
    return obj->compareFloat(this);
}

int FloatNumber::compareInt(const IntNumber* obj) const throw (Errors::RuntimeError) {
  float temp = obj->getValue() - value;

  if (temp > 0.0)
    return 1;
  else if (temp < 0.0)
    return -1;
  else
    return 0;
}

int FloatNumber::compareFloat(const FloatNumber* obj) const throw (Errors::RuntimeError) {
  float temp = obj->value - value;

  if (temp > 0.0)
    return 1;
  else if (temp < 0.0)
    return -1;
  else
    return 0;
}

Object* FloatNumber::negate() throw (Errors::RuntimeError) {
  return VM::getAllocator().createFloatNumber(-value);
}

Object* FloatNumber::add(Object* obj) throw (Errors::RuntimeError) {
  return obj->addFloat(this);
}

Object* FloatNumber::addInt(IntNumber* obj) throw (Errors::RuntimeError) {
  return VM::getAllocator().createFloatNumber(value + obj->getValue());
}

Object* FloatNumber::addFloat(FloatNumber* obj) throw (Errors::RuntimeError) {
  return VM::getAllocator().createFloatNumber(value + obj->value);
}

Object* FloatNumber::sub(Object* obj) throw (Errors::RuntimeError) {
  return obj->subFloat(this);
}

Object* FloatNumber::subInt(IntNumber* obj) throw (Errors::RuntimeError) {
  return VM::getAllocator().createFloatNumber(obj->getValue() - value);
}

Object* FloatNumber::subFloat(FloatNumber* obj) throw (Errors::RuntimeError) {
  return VM::getAllocator().createFloatNumber(obj->value - value);
}

Object* FloatNumber::mul(Object* obj) throw (Errors::RuntimeError) {
  return obj->mulFloat(this);
}

Object* FloatNumber::mulInt(IntNumber* obj) throw (Errors::RuntimeError) {
  return VM::getAllocator().createFloatNumber(obj->getValue() * value);
}

Object* FloatNumber::mulFloat(FloatNumber* obj) throw (Errors::RuntimeError) {
  return VM::getAllocator().createFloatNumber(obj->value * value);
}

Object* FloatNumber::div(Object* obj) throw (Errors::RuntimeError) {
  return obj->divFloat(this);
}

Object* FloatNumber::divInt(IntNumber* obj) throw (Errors::RuntimeError) {
  return VM::getAllocator().createFloatNumber(obj->getValue() / value);
}

Object* FloatNumber::divFloat(FloatNumber* obj) throw (Errors::RuntimeError) {
  return VM::getAllocator().createFloatNumber(obj->value / value);
}

Object* FloatNumber::remainder(Object* obj) throw (Errors::RuntimeError) {
  return obj->remainderFloat(this);
}

Object* FloatNumber::remainderFloat(FloatNumber* obj) throw (Errors::RuntimeError) {
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
