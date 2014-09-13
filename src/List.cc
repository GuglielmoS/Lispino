#include "List.h"

#include <sstream>

#include "VM.h"

namespace Lispino {

List::List() 
    : head(nullptr), tail(nullptr), cachedArgs(false) {
  /* DO NOTHING */
}

List::List(Object* head, Object* tail)
    : head(head), tail(tail), cachedArgs(false) {
  /* DO NOTHING */
}

void List::setFirst(Object *first) {
  head = first;
}

void List::setRest(Object *rest) {
  tail = rest;
  cachedArgs = false;
}

Object* List::getFirst() {
  return head;
}

Object* List::getRest() {
  return tail;
}

Object* List::eval(Environment& env) {
  if (head->isNil())
    return VM::getAllocator().createNil();

  // extract the arguments
  if (!cachedArgs)
    updateCachedArguments();

  // execute the call
  Object *op = head->eval(env);
  if (op->isBuiltinFunction()) {
    return static_cast<Builtins::BuiltinFunction*>(op)->apply(args, env);
  } else {
    // evaluate the arguments
    std::vector<Object*> evaluatedArgs;
    for (auto& current_arg : args)
      evaluatedArgs.push_back(current_arg->eval(env));

    if (op->isLambda()) {
      Closure *closure = static_cast<Closure*>(op->eval(env));

      // prevent the closure from being removed by the GC
      env.put(VM::getAllocator().createRandomSymbol(), closure);

      // execute the closure and return the result
      return closure->apply(evaluatedArgs);
    } else if (op->isClosure()) {
      return static_cast<Closure*>(op)->apply(evaluatedArgs);
    } else {
      throw std::runtime_error("Invalid function call, the operator cannot be used: " + op->toString());
    }
  }
}

int List::compare(Object* obj) {
  return obj->compareList(this);
}

int List::compareList(List* obj) {
  if (obj == this)
    return 0;
  else
    return -1;
}

bool List::isList() const {
  return true;
}

void List::mark() {
  // mark the current object
  Object::mark();

  // mark its sub-components
  head->mark();
  tail->mark();
  for (auto& current_arg : args)
    current_arg->mark();
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

void List::updateCachedArguments() {
  args.clear();
  cachedArgs = true;

  if (tail != nullptr) {
    List *current = nullptr;

    if (tail->isList()) {
      current = static_cast<List*>(tail);

      while (!current->isNil()) {
        if (current->head != nullptr) {
          args.push_back(current->head);
          if (!current->tail->isNil()) {
            if (current->tail->isList()) {
              current = static_cast<List*>(current->tail);
            } else {
              args.push_back(current->tail);
              break;
            }
          } else {
            break;
          }
        } else {
          break;
        }
      }
    } else if (!tail->isNil()) {
      args.push_back(tail);
    }
  }
}

}
