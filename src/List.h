#ifndef LISPINO_LIST_H_
#define LISPINO_LIST_H_

#include <vector>
#include <string>

#include "Object.h"

namespace Lispino {

class List : public Object {
 public:
  List();

  List(Object* head, Object* tail);

  void setFirst(Object *first);

  void setRest(Object *rest);

  Object* getFirst();

  Object* getRest();

  Object* eval(Environment& env);

  int compare(Object* obj);

  int compareList(List* obj);

  void mark();

  bool isList() const;

  std::string toString() const;

 private:
  Object *head;

  Object *tail;

  std::vector<Object*> args;

  bool cachedArgs;

  std::string toStringHelper(bool parentheses) const;

  void updateCachedArguments();
};

}

#endif // LISPINO_LIST_H_
