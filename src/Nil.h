#ifndef LISPINO_NIL_H_
#define LISPINO_NIL_H_

#include "Object.h"

namespace Lispino {

class Nil : public Object {
 public:
  Object* eval(Environment* env) throw (Errors::RuntimeError) override;

  int compare(const Object* obj) const throw (Errors::RuntimeError) override;

  int compareNil(const Nil* obj) const throw (Errors::RuntimeError) override;

  int compareList(const List* obj) const throw (Errors::RuntimeError) override;
  
  int compareInt(const IntNumber* obj) const throw (Errors::RuntimeError) override;
  
  int compareFloat(const FloatNumber* obj) const throw (Errors::RuntimeError) override;
  
  int compareSymbol(const Symbol* obj) const throw (Errors::RuntimeError) override;
  
  int compareString(const String* obj) const throw (Errors::RuntimeError) override;
  
  int compareBoolean(const Boolean* obj) const throw (Errors::RuntimeError) override;
  
  int compareSequence(const Sequence* obj) const throw (Errors::RuntimeError) override;

  bool isNil() const override;

  std::string toString() const override;
};

}

#endif // LISPINO_NIL_H_
