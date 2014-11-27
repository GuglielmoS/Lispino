#include "Object.h"

#include <stdexcept>

#include "VM.h"

namespace Lispino {

Object::Object(ObjectType type) : type(type), markFlag(false) {
  /* DO NOTHING */
}

/// default destructor
Object::~Object() {
  /* DO NOTHING */
}

bool Object::eqv(const Object* obj) const {
  return this->eq(obj);
}

bool Object::eqvInt(const IntNumber* obj) const {
  return this->eq(obj);
}

bool Object::eqvFloat(const FloatNumber* obj) const {
  return this->eq(obj);
}

bool Object::eqvCharacter(const Character* obj) const {
  return this->eq(obj);
}

bool Object::equal(const Object* obj) const {
  return this->eqv(obj);
}

bool Object::equalString(const String* obj) const {
  return this->eqv(obj);
}

bool Object::equalList(const List* obj) const {
  return this->eqv(obj);
}

int Object::compare(const Object*) const throw(Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot compare apples and pears!"*/);
}

int Object::compareNil(const Nil*) const throw(Errors::RuntimeError) {
  return -1;
}

int Object::compareList(const List*) const throw(Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot compare apples and pears!"*/);
}

int Object::compareInt(const IntNumber*) const throw(Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot compare apples and pears!"*/);
}

int Object::compareFloat(const FloatNumber*) const throw(Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot compare apples and pears!"*/);
}

int Object::compareSymbol(const Symbol*) const throw(Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot compare apples and pears!"*/);
}

int Object::compareCharacter(const Character*) const throw(Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot compare apples and pears!"*/);
}

int Object::compareString(const String*) const throw(Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot compare apples and pears!"*/);
}

int Object::compareBoolean(const Boolean*) const throw(Errors::RuntimeError) {
  throw Errors::RuntimeError(/*"Cannot compare apples and pears!"*/);
}

bool Object::isTrue() const {
  return true;
}

bool Object::isFalse() const {
  return false;
}
}
