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

Object* List::eval(Environment* env) throw (Errors::RuntimeError) {
  // return NIL if the list is empty
  if (head->isNil())
    return VM::getAllocator().createNil();

  // extract the arguments if needed
  if (!cachedArgs)
    updateCachedArguments();

  // evaluate the list's head if needed (-> it's not a lambda)
  Object *op = head;
  if (!op->isLambda())
    op = head->eval(env);

  // apply the other values to the evaluated operator accordingly to the fact
  // that it can be either a builtin function or a lambda object 
  if (op->isBuiltinFunction()) {
    return static_cast<Builtins::BuiltinFunction*>(op)->apply(args, env);
  } else {
    // evaluate the arguments
    std::vector<Object*> evaluated_args;
    for (auto& current_arg : args)
      evaluated_args.push_back(current_arg->eval(env));

    // the pointer to the lambda code to evaluate
    Lambda *lambda = nullptr;

    // the pointer to the environment to use for the evaluation
    Environment *eval_env = env;

    // retrieve the lambda and the environment where the code must be evaluated
    if (op->isLambda()) {
      lambda = static_cast<Lambda*>(op);
    } else if (op->isClosure()) {
      lambda = static_cast<Closure*>(op)->getLambda();
      eval_env = static_cast<Closure*>(op)->getEnv();
    }
    else {
      throw Errors::RuntimeError(/*"Invalid function call, the operator cannot be called!"*/);
    }

    // apply the arguments to the lambda and return the result
    return lambda->apply(evaluated_args, eval_env);
  }
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
