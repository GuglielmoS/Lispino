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

  Object* eval(Environment* env) throw (Errors::RuntimeError) override;

  int compare(const Object* obj) const throw (Errors::RuntimeError) override;

  int compareList(const List* obj) const throw (Errors::RuntimeError) override;

  void mark() override;

  bool isList() const override;

  std::string toString() const override;

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
