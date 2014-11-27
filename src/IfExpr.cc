#include "IfExpr.h"

#include <stdexcept>

#include "Boolean.h"

namespace Lispino {

IfExpr::IfExpr() : Object(ObjectType::IF), condition(nullptr), consequent(nullptr), alternative(nullptr) {
  /* DO NOTHING */
}

void IfExpr::setCondition(Object* condition) {
  this->condition = condition;
}

void IfExpr::setConsequent(Object* consequent) {
  this->consequent = consequent;
}

void IfExpr::setAlternative(Object* alternative) {
  this->alternative = alternative;
}

Object* IfExpr::getCondition() {
  return condition;
}

Object* IfExpr::getConsequent() {
  return consequent;
}

Object* IfExpr::getAlternative() {
  return alternative;
}

std::string IfExpr::toString() const {
  return "IF";
}
}
