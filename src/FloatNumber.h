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

  Object* eval(Environment* env) override;

  int compare(const Object* obj) const override;

  int compareInt(const IntNumber* obj) const override;

  int compareFloat(const FloatNumber* obj) const override;

  Object* negate() override;

  Object* add(Object* obj) override;

  Object* addInt(IntNumber* obj) override;

  Object* addFloat(FloatNumber* obj) override;

  Object* sub(Object* obj) override;

  Object* subInt(IntNumber* obj) override;

  Object* subFloat(FloatNumber* obj) override;

  Object* mul(Object* obj) override;

  Object* mulInt(IntNumber* obj) override;

  Object* mulFloat(FloatNumber* obj) override;

  Object* div(Object* obj) override;

  Object* divInt(IntNumber* obj) override;

  Object* divFloat(FloatNumber* obj) override;

  Object* remainder(Object* obj) override;

  Object* remainderFloat(FloatNumber* obj) override;

  bool isAtom() const override;

  bool isFloatNumber() const override;

  std::string toString() const override;

 private:
  double value;
};

}

#endif // LISPINO_FLOATNUMBER_H_
