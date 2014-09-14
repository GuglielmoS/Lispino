#ifndef LISPINO_INTNUMBER_H_
#define LISPINO_INTNUMBER_H_

#include <sstream>
#include <string>

#include "Object.h"

namespace Lispino {

class IntNumber : public Object {
 public:
  IntNumber();

  IntNumber(long int value);

  void setValue(long int value);

  long int getValue() const;

  Object* eval(Environment& env);

  int compare(const Object* obj) const;

  int compareInt(const IntNumber* obj) const;

  int compareFloat(const FloatNumber* obj) const;
  
  Object* negate();

  Object* add(Object* obj);

  Object* addInt(IntNumber* obj);

  Object* addFloat(FloatNumber* obj);

  Object* sub(Object* obj);
  
  Object* subInt(IntNumber* obj);
  
  Object* subFloat(FloatNumber* obj);
  
  Object* mul(Object* obj);
  
  Object* mulInt(IntNumber* obj);
  
  Object* mulFloat(FloatNumber* obj);
  
  Object* div(Object* obj);
  
  Object* divInt(IntNumber* obj);
  
  Object* divFloat(FloatNumber* obj);
  
  Object* remainder(Object* obj);
  
  Object* remainderInt(IntNumber* obj);

  bool isAtom() const;
  
  bool isIntNumber() const;

  std::string toString() const;

 private:
  long int value;
};

}

#endif // LISPINO_INTNUMBER_H_
