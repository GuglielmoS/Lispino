#include "List.h"

#include <sstream>

#include "VM.h"

namespace Lispino {

List::List() 
    : Object(ObjectType::LIST), head(nullptr), tail(nullptr) {
  /* DO NOTHING */
}

List::List(Object* head, Object* tail)
    : Object(ObjectType::LIST), head(head), tail(tail) {
  /* DO NOTHING */
}

void List::setFirst(Object *first) {
  head = first;
}

void List::setRest(Object *rest) {
  tail = rest;
}

Object* List::getFirst() {
  return head;
}

Object* List::getRest() {
  return tail;
}

bool List::equal(const Object* obj) const {
  return obj->equalList(this);
}

bool List::equalList(const List* obj) const {
  if (head->eqv(obj->head))
    return tail->equal(obj->tail);

  return false;
}

int List::compare(const Object* obj) const throw (Errors::RuntimeError) {
  return obj->compareList(this);
}

int List::compareList(const List* obj) const throw (Errors::RuntimeError) {
  if (obj == this)
    return 0;
  else
    return -1;
}

std::string List::toString() const {
  return toStringHelper(true);
}

std::string List::toStringHelper(bool parentheses) const {
  std::stringstream buf;
  if (parentheses)
    buf << "(";

  if (!head->isNil())
    buf << head->toString();

  if (!tail->isNil()) {
    if (tail->isList() || tail->isQuote() || tail->isDefine() || tail->isLambda())
      buf << " ";
    else
      buf << " . ";

    if (tail->isList())
      buf << static_cast<List*>(tail)->toStringHelper(false);
    else
      buf << tail->toString();
  }

  if (parentheses)
    buf << ")";

  return buf.str();   
} 

}
