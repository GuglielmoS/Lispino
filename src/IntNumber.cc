#include "IntNumber.h"

#include <cmath>

#include <sstream>

#include "FloatNumber.h"
#include "VM.h"

namespace Lispino {

IntNumber::IntNumber() : Number(ObjectType::INT_NUMBER), value(0) {
  /* DO NOTHING */
}

IntNumber::IntNumber(std::int64_t value) 
    : Number(ObjectType::INT_NUMBER), value(value) {
  /* DO NOTHING */
}

void IntNumber::setValue(std::int64_t value) {
  this->value = value;
}

std::int64_t IntNumber::getValue() const {
  return value;
}

bool IntNumber::eqv(const Object* obj) const {
  return obj->eqvInt(this);
}

bool IntNumber::eqvInt(const IntNumber* obj) const {
  return value == obj->value;
}

int IntNumber::compare(const Object* obj) const throw (Errors::RuntimeError) {
  if (obj == this)
    return 0;
  else
    return obj->compareInt(this);
}

int IntNumber::compareInt(const IntNumber* obj) const throw (Errors::RuntimeError) {
  return obj->value - value;
}

int IntNumber::compareFloat(const FloatNumber* obj) const throw (Errors::RuntimeError) {
  double temp = obj->getValue() - value;

  if (temp > 0.0)
    return 1;
  else if (temp < 0.0)
    return -1;
  else
    return 0;
}

Object* IntNumber::negate() throw (Errors::RuntimeError) {
  return VM::getAllocator().createIntNumber(-value);
}

Number* IntNumber::add(Number* obj) throw (Errors::RuntimeError) {
  return obj->addInt(this);
}

Number* IntNumber::addInt(IntNumber* obj) throw (Errors::RuntimeError) {
  return VM::getAllocator().createIntNumber(value + obj->value);
}

Number* IntNumber::addFloat(FloatNumber* obj) throw (Errors::RuntimeError) {
  return VM::getAllocator().createIntNumber(value + obj->getValue());
}

Number* IntNumber::sub(Number* obj) throw (Errors::RuntimeError) {
  return obj->subInt(this);
}

Number* IntNumber::subInt(IntNumber* obj) throw (Errors::RuntimeError) {
  return VM::getAllocator().createIntNumber(obj->value - value);
}

Number* IntNumber::subFloat(FloatNumber* obj) throw (Errors::RuntimeError) {
  return VM::getAllocator().createFloatNumber(obj->getValue() - value);
}

Number* IntNumber::mul(Number* obj) throw (Errors::RuntimeError) {
  return obj->mulInt(this);
}

Number* IntNumber::mulInt(IntNumber* obj) throw (Errors::RuntimeError) {
  return VM::getAllocator().createIntNumber(obj->value * value);
}

Number* IntNumber::mulFloat(FloatNumber* obj) throw (Errors::RuntimeError) {
  return VM::getAllocator().createFloatNumber(obj->getValue() * value);
}

Number* IntNumber::div(Number* obj) throw (Errors::RuntimeError) {
  return obj->divInt(this);
}

Number* IntNumber::divInt(IntNumber* obj) throw (Errors::RuntimeError) {
  if (value == 0)
    throw Errors::RuntimeError("error: division by zero");

  return VM::getAllocator().createIntNumber(obj->value / value);
}

Number* IntNumber::divFloat(FloatNumber* obj) throw (Errors::RuntimeError) {
  if (value == 0)
    throw Errors::RuntimeError("error: division by zero");

  return VM::getAllocator().createFloatNumber(obj->getValue() / value);
}

Number* IntNumber::remainder(Number* obj) throw (Errors::RuntimeError) {
  return obj->remainderInt(this);
}

Number* IntNumber::remainderInt(IntNumber* obj) throw (Errors::RuntimeError) {
  if (value == 0)
    throw Errors::RuntimeError("error: division by zero");

  return VM::getAllocator().createIntNumber(obj->value % value);
}

Number* IntNumber::remainderFloat(FloatNumber* obj) throw (Errors::RuntimeError) {
  if (value == 0)
    throw Errors::RuntimeError("error: division by zero");

  return VM::getAllocator().createIntNumber(fmod(obj->getValue(), value));
}

std::string IntNumber::toString() const {
  std::stringstream buf;
  buf << value;
  return buf.str();
}

}
