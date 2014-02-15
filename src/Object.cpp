#include "Object.h"
#include "VM.h"

using namespace Lispino;

Object* Object::eval() {
    return eval(VM::getGlobalEnv());
}

int Object::compare(Object* obj) {
    throw std::runtime_error("compare: invalid data types!");
}

int Object::compareNil(Nil* obj) {
    return -1;
}

int Object::compareList(List* obj) {
    throw std::runtime_error("compare: invalid data types!");
}

int Object::compareInt(IntNumber* obj) {
    throw std::runtime_error("compare: invalid data types!");
}

int Object::compareFloat(FloatNumber* obj) {
    throw std::runtime_error("compare: invalid data types!");
}

int Object::compareSymbol(Symbol* obj) {
    throw std::runtime_error("compare: invalid data types!");
}

int Object::compareString(String* obj) {
    throw std::runtime_error("compare: invalid data types!");
}

int Object::compareBoolean(Boolean* obj) {
    throw std::runtime_error("compare: invalid data types!");
}

Object* Object::add(Object* obj) {
    throw std::runtime_error("+: invalid data types!");
}

Object* Object::addInt(IntNumber* obj) {
    throw std::runtime_error("+: invalid data types!");
}

Object* Object::addFloat(FloatNumber* obj) {
    throw std::runtime_error("+: invalid data types!");
}

Object* Object::addString(String* obj) {
    throw std::runtime_error("+: invalid data types!");
}

Object* Object::sub(Object* obj) {
    throw std::runtime_error("-: invalid data types!");
}

Object* Object::subInt(IntNumber* obj) {
    throw std::runtime_error("-: invalid data types!");
}

Object* Object::subFloat(FloatNumber* obj) {
    throw std::runtime_error("-: invalid data types!");
}

Object* Object::mul(Object* obj) {
    throw std::runtime_error("*: invalid data types!");
}

Object* Object::mulInt(IntNumber* obj) {
    throw std::runtime_error("*: invalid data types!");
}

Object* Object::mulFloat(FloatNumber* obj) {
    throw std::runtime_error("*: invalid data types!");
}

Object* Object::div(Object* obj) {
    throw std::runtime_error("/: invalid data types!");
}

Object* Object::divInt(IntNumber* obj) {
    throw std::runtime_error("/: invalid data types!");
}

Object* Object::divFloat(FloatNumber* obj) {
    throw std::runtime_error("/: invalid data types!");
}

Object* Object::remainder(Object* obj) {
    throw std::runtime_error("remainder: invalid data types!");
}

Object* Object::remainderInt(IntNumber* obj) {
    throw std::runtime_error("remainder: invalid data types!");
}

Object* Object::remainderFloat(FloatNumber* obj) {
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
