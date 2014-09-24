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

  bool equal(const Object* obj) const override;

  bool equalList(const List* obj) const override;

  int compare(const Object* obj) const throw (Errors::RuntimeError) override;

  int compareList(const List* obj) const throw (Errors::RuntimeError) override;

  void mark() override;

  std::string toString() const override;

 private:
  Object *head;

  Object *tail;

  std::vector<Object*> args;

  bool cachedArgs;

  std::string toStringHelper(bool parentheses) const;
};

}

#endif // LISPINO_LIST_H_
