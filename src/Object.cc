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

Object* Object::eval() {
  return eval(&VM::getGlobalEnv());
}

int Object::compare(const Object*) const {
  throw std::runtime_error("compare: invalid data types!");
}

int Object::compareNil(const Nil*) const {
  return -1;
}

int Object::compareList(const List*) const {
  throw std::runtime_error("compare: invalid data types!");
}

int Object::compareInt(const IntNumber*) const {
  throw std::runtime_error("compare: invalid data types!");
}

int Object::compareFloat(const FloatNumber*) const {
  throw std::runtime_error("compare: invalid data types!");
}

int Object::compareSymbol(const Symbol*) const {
  throw std::runtime_error("compare: invalid data types!");
}

int Object::compareString(const String*) const {
  throw std::runtime_error("compare: invalid data types!");
}

int Object::compareBoolean(const Boolean*) const {
  throw std::runtime_error("compare: invalid data types!");
}

int Object::compareSequence(const Sequence*) const {
  throw std::runtime_error("compare: invalid data types!");
}

Object* Object::negate() {
  throw std::runtime_error("negate: invalid data type!");
}

Object* Object::add(Object*) {
  throw std::runtime_error("+: invalid data types!");
}

Object* Object::addInt(IntNumber*) {
  throw std::runtime_error("+: invalid data types!");
}

Object* Object::addFloat(FloatNumber*) {
  throw std::runtime_error("+: invalid data types!");
}

Object* Object::addString(String*) {
  throw std::runtime_error("+: invalid data types!");
}

Object* Object::sub(Object*) {
  throw std::runtime_error("-: invalid data types!");
}

Object* Object::subInt(IntNumber*) {
  throw std::runtime_error("-: invalid data types!");
}

Object* Object::subFloat(FloatNumber*) {
  throw std::runtime_error("-: invalid data types!");
}

Object* Object::mul(Object*) {
  throw std::runtime_error("*: invalid data types!");
}

Object* Object::mulInt(IntNumber*) {
  throw std::runtime_error("*: invalid data types!");
}

Object* Object::mulFloat(FloatNumber*) {
  throw std::runtime_error("*: invalid data types!");
}

Object* Object::div(Object*) {
  throw std::runtime_error("/: invalid data types!");
}

Object* Object::divInt(IntNumber*) {
  throw std::runtime_error("/: invalid data types!");
}

Object* Object::divFloat(FloatNumber*) {
  throw std::runtime_error("/: invalid data types!");
}

Object* Object::remainder(Object*) {
  throw std::runtime_error("remainder: invalid data types!");
}

Object* Object::remainderInt(IntNumber*) {
  throw std::runtime_error("remainder: invalid data types!");
}

Object* Object::remainderFloat(FloatNumber*) {
  throw std::runtime_error("remainder: invalid data types!");
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
