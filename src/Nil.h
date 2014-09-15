#ifndef LISPINO_NIL_H_
#define LISPINO_NIL_H_

#include "Object.h"

namespace Lispino {

class Nil : public Object {
 public:
  Object* eval(Environment* env) override;

  int compare(const Object* obj) const override;

  int compareNil(const Nil* obj) const override;

  int compareList(const List* obj) const override;
  
  int compareInt(const IntNumber* obj) const override;
  
  int compareFloat(const FloatNumber* obj) const override;
  
  int compareSymbol(const Symbol* obj) const override;
  
  int compareString(const String* obj) const override;
  
  int compareBoolean(const Boolean* obj) const override;
  
  int compareSequence(const Sequence* obj) const override;

  bool isNil() const override;

  std::string toString() const override;
};

}

#endif // LISPINO_NIL_H_
