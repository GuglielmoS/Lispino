#include "Object.h"

#include <stdexcept>

#include "VM.h"

namespace Lispino {

Object::Object() : markFlag(false) {
  /* DO NOTHING */
}

/// default destructor
Object::~Object() {
  /* DO NOTHING */
}

Object* Object::eval() throw (Errors::RuntimeError) {
  return eval(&VM::getGlobalEnv());
}

int Object::compare(const Object*) const throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot compare apples and pears!"*/);
}

int Object::compareNil(const Nil*) const throw (Errors::RuntimeError) {
  return -1;
}

int Object::compareList(const List*) const throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot compare apples and pears!"*/);
}

int Object::compareInt(const IntNumber*) const throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot compare apples and pears!"*/);
}

int Object::compareFloat(const FloatNumber*) const throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot compare apples and pears!"*/);
}

int Object::compareSymbol(const Symbol*) const throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot compare apples and pears!"*/);
}

int Object::compareString(const String*) const throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot compare apples and pears!"*/);
}

int Object::compareBoolean(const Boolean*) const throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot compare apples and pears!"*/);
}

int Object::compareSequence(const Sequence*) const throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot compare apples and pears!"*/);
}

Object* Object::negate() throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot negate this!"*/);
}

Object* Object::add(Object*) throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot add apples and pears!"*/);
}

Object* Object::addInt(IntNumber*) throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot add apples and pears!"*/);
}

Object* Object::addFloat(FloatNumber*) throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot add apples and pears!"*/);
}

Object* Object::addString(String*) throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot add apples and pears!"*/);
}

Object* Object::sub(Object*) throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot sub apples and pears!"*/);
}

Object* Object::subInt(IntNumber*) throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot sub apples and pears!"*/);
}

Object* Object::subFloat(FloatNumber*) throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot sub apples and pears!"*/);
}

Object* Object::mul(Object*) throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot mul apples and pears!"*/);
}

Object* Object::mulInt(IntNumber*) throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot mul apples and pears!"*/);
}

Object* Object::mulFloat(FloatNumber*) throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot mul apples and pears!"*/);
}

Object* Object::div(Object*) throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot div apples and pears!"*/);
}

Object* Object::divInt(IntNumber*) throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot div apples and pears!"*/);
}

Object* Object::divFloat(FloatNumber*) throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot div apples and pears!"*/);
}

Object* Object::remainder(Object*) throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot calculate the remainder between apples and pears!"*/);
}

Object* Object::remainderInt(IntNumber*) throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot calculate the remainder between apples and pears!"*/);
}

Object* Object::remainderFloat(FloatNumber*) throw (Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot calculate the remainder between apples and pears!"*/);
}

void Object::mark() {
  markFlag = true;
}

void Object::unmark() {
  markFlag = false;
}

bool Object::isMarked() const {
  return markFlag;
}

bool Object::isNil() const {
  return false;
}

bool Object::isAtom() const {
  return false;
}

bool Object::isList() const {
  return false;
}

bool Object::isLambda() const {
  return false;
}

bool Object::isClosure() const {
  return false;
}

bool Object::isIntNumber() const {
  return false;
}

bool Object::isFloatNumber() const {
  return false;
}

bool Object::isBoolean() const {
  return false;
}

bool Object::isSymbol() const {
  return false;
}

bool Object::isString() const {
  return false;
}

bool Object::isQuote() const {
  return false;
}

bool Object::isDefine() const {
  return false;
}

bool Object::isIfExpr() const {
  return false;
}

bool Object::isBuiltinFunction() const {
  return false;
}

bool Object::isSequence() const {
  return false;
}

}
