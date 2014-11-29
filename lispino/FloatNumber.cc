#include "FloatNumber.h"

#include <cmath>

#include <sstream>

#include "IntNumber.h"
#include "VM.h"

namespace lispino {

FloatNumber::FloatNumber() : Number(ObjectType::FLOAT_NUMBER), value(0.0) {
  /* DO NOTHING */
}

FloatNumber::FloatNumber(double value) : Number(ObjectType::FLOAT_NUMBER), value(value) {
  /* DO NOTHING */
}

void FloatNumber::setValue(double value) {
  this->value = value;
}

double FloatNumber::getValue() const {
  return value;
}

bool FloatNumber::eqv(const Object* obj) const {
  return obj->eqvFloat(this);
}

bool FloatNumber::eqvFloat(const FloatNumber* obj) const {
  return value == obj->value;
}

int FloatNumber::compare(const Object* obj) const throw(errors::RuntimeError) {
  if (obj == this)
    return 0;
  else
    return obj->compareFloat(this);
}

int FloatNumber::compareInt(const IntNumber* obj) const throw(errors::RuntimeError) {
  float temp = obj->getValue() - value;

  if (temp > 0.0)
    return 1;
  else if (temp < 0.0)
    return -1;
  else
    return 0;
}

int FloatNumber::compareFloat(const FloatNumber* obj) const throw(errors::RuntimeError) {
  float temp = obj->value - value;

  if (temp > 0.0)
    return 1;
  else if (temp < 0.0)
    return -1;
  else
    return 0;
}

Number* FloatNumber::negate() throw(errors::RuntimeError) {
  return VM::getAllocator().createFloatNumber(-value);
}

Number* FloatNumber::add(Number* obj) throw(errors::RuntimeError) {
  return obj->addFloat(this);
}

Number* FloatNumber::addInt(IntNumber* obj) throw(errors::RuntimeError) {
  return VM::getAllocator().createFloatNumber(value + obj->getValue());
}

Number* FloatNumber::addFloat(FloatNumber* obj) throw(errors::RuntimeError) {
  return VM::getAllocator().createFloatNumber(value + obj->value);
}

Number* FloatNumber::sub(Number* obj) throw(errors::RuntimeError) {
  return obj->subFloat(this);
}

Number* FloatNumber::subInt(IntNumber* obj) throw(errors::RuntimeError) {
  return VM::getAllocator().createFloatNumber(obj->getValue() - value);
}

Number* FloatNumber::subFloat(FloatNumber* obj) throw(errors::RuntimeError) {
  return VM::getAllocator().createFloatNumber(obj->value - value);
}

Number* FloatNumber::mul(Number* obj) throw(errors::RuntimeError) {
  return obj->mulFloat(this);
}

Number* FloatNumber::mulInt(IntNumber* obj) throw(errors::RuntimeError) {
  return VM::getAllocator().createFloatNumber(obj->getValue() * value);
}

Number* FloatNumber::mulFloat(FloatNumber* obj) throw(errors::RuntimeError) {
  return VM::getAllocator().createFloatNumber(obj->value * value);
}

Number* FloatNumber::div(Number* obj) throw(errors::RuntimeError) {
  return obj->divFloat(this);
}

Number* FloatNumber::divInt(IntNumber* obj) throw(errors::RuntimeError) {
  if (value == 0)
    throw errors::RuntimeError("error: division by zero");

  return VM::getAllocator().createFloatNumber(obj->getValue() / value);
}

Number* FloatNumber::divFloat(FloatNumber* obj) throw(errors::RuntimeError) {
  if (value == 0)
    throw errors::RuntimeError("error: division by zero");

  return VM::getAllocator().createFloatNumber(obj->value / value);
}

Number* FloatNumber::remainder(Number* obj) throw(errors::RuntimeError) {
  return obj->remainderFloat(this);
}

Number* FloatNumber::remainderInt(IntNumber* obj) throw(errors::RuntimeError) {
  if (value == 0)
    throw errors::RuntimeError("error: division by zero");

  return VM::getAllocator().createIntNumber(fmod(obj->getValue(), value));
}

Number* FloatNumber::remainderFloat(FloatNumber* obj) throw(errors::RuntimeError) {
  if (value == 0)
    throw errors::RuntimeError("error: division by zero");

  return VM::getAllocator().createIntNumber(fmod(obj->value, value));
}

std::string FloatNumber::toString() const {
  std::stringstream buf;
  buf << value;
  return buf.str();
}
}
