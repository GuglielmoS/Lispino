#ifndef LISPINO_NIL_H_
#define LISPINO_NIL_H_

#include "Object.h"

namespace Lispino {

class Nil : public Object {
 public:
  Object* eval(Environment& env);

  int compare(const Object* obj) const;

  int compareNil(const Nil* obj) const;

  int compareList(const List* obj) const;
  
  int compareInt(const IntNumber* obj) const;
  
  int compareFloat(const FloatNumber* obj) const;
  
  int compareSymbol(const Symbol* obj) const;
  
  int compareString(const String* obj) const;
  
  int compareBoolean(const Boolean* obj) const;
  
  int compareSequence(const Sequence* obj) const;

  bool isNil() const;

  std::string toString() const;
};

}

#endif // LISPINO_NIL_H_
