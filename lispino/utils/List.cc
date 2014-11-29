#include "List.h"

#include "../VM.h"

namespace lispino {

namespace utils {

std::vector<Object*> list2vec(List* list) {
  std::vector<Object*> args;

  List *current = static_cast<List*>(list->getRest());

  while (!current->isNil()) {
    if (current->getFirst() != nullptr) {
      args.push_back(current->getFirst());
      if (!current->getRest()->isNil()) {
        if (current->getRest()->isList()) {
          current = static_cast<List*>(current->getRest());
        } else {
          args.push_back(current->getRest());
          break;
        }
      } else {
        break;
      }
    } else {
      break;
    }
  }

  return args;
}

List* vec2list(std::vector<Object*>& objects) {
  List *last_cons = nullptr;
  List *first_cons = nullptr;

  for (auto& current_object : objects) {
    List *new_cons = VM::getAllocator().createList(current_object, VM::getAllocator().createNil());

    if (last_cons == nullptr) {
      first_cons = new_cons;
      last_cons = new_cons;
    } else {
      last_cons->setRest(new_cons);
      last_cons = static_cast<List*>(last_cons->getRest());
    }
  }

  if (first_cons == nullptr)
    return VM::getAllocator().createList(nullptr, nullptr);
  else
    return first_cons;
}
}
}
