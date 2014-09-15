#ifndef LISPINO_FLOATNUMBER_H_
#define LISPINO_FLOATNUMBER_H_

#include <sstream>
#include <string>

#include "Object.h"

namespace Lispino {

class FloatNumber : public Object {
 public:
  FloatNumber();

  FloatNumber(double value);

  void setValue(double value);

  double getValue() const;

  Object* eval(Environment* env);

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

  Object* remainderFloat(FloatNumber* obj);

  bool isAtom() const;

  bool isFloatNumber() const;

  std::string toString() const;

 private:
  double value;
};

}

#endif // LISPINO_FLOATNUMBER_H_
