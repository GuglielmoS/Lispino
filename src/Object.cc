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

ObjectType Object::getType() const {
  return type;
}

Object* Object::eval() throw (Errors::RuntimeError) {
  return VM::getEvaluator().eval(this);
}

Object* Object::eval(std::shared_ptr<Environment> env) throw (Errors::RuntimeError) {
  return VM::getEvaluator().eval(this, env);
}

bool Object::eq(const Object* obj) const {
  return this == obj;
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

int Object::compareCharacter(const Character*) const throw (Errors::RuntimeError) {
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

bool Object::isTrue() const {
  return true;
}

bool Object::isFalse() const {
  return false;
}

bool Object::isNil() const {
  return type == ObjectType::NIL;
}

bool Object::isList() const {
  return type == ObjectType::LIST;
}

bool Object::isLambda() const {
  return type == ObjectType::LAMBDA;
}

bool Object::isClosure() const {
  return type == ObjectType::CLOSURE;
}

bool Object::isPromise() const {
  return type == ObjectType::PROMISE;
}

bool Object::isIntNumber() const {
  return type == ObjectType::INT_NUMBER;
}

bool Object::isFloatNumber() const {
  return type == ObjectType::FLOAT_NUMBER;
}

bool Object::isBoolean() const {
  return type == ObjectType::BOOLEAN;
}

bool Object::isSymbol() const {
  return type == ObjectType::SYMBOL;
}

bool Object::isCharacter() const {
  return type == ObjectType::CHARACTER;
}

bool Object::isString() const {
  return type == ObjectType::STRING;
}

bool Object::isQuote() const {
  return type == ObjectType::QUOTE;
}

bool Object::isDefine() const {
  return type == ObjectType::DEFINE;
}

bool Object::isIfExpr() const {
  return type == ObjectType::IF;
}

bool Object::isBuiltinFunction() const {
  return type == ObjectType::BUILTIN_FUNCTION;
}

bool Object::isSequence() const {
  return type == ObjectType::SEQUENCE;
}

}
