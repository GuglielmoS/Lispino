#ifndef LISPINO_FLOATNUMBER_H_
#define LISPINO_FLOATNUMBER_H_

#include "Number.h"

namespace Lispino {

class FloatNumber : public Number {
 public:
  FloatNumber();

  explicit FloatNumber(double value);

  void setValue(double value);

  double getValue() const;

  bool eqv(const Object* obj) const override;

  bool eqvFloat(const FloatNumber* obj) const override;

  int compare(const Object* obj) const throw(Errors::RuntimeError) override;

  int compareInt(const IntNumber* obj) const throw(Errors::RuntimeError) override;

  int compareFloat(const FloatNumber* obj) const throw(Errors::RuntimeError) override;

  Number* negate() throw(Errors::RuntimeError) override;

  Number* add(Number* obj) throw(Errors::RuntimeError) override;

  Number* addInt(IntNumber* obj) throw(Errors::RuntimeError) override;

  Number* addFloat(FloatNumber* obj) throw(Errors::RuntimeError) override;

  Number* sub(Number* obj) throw(Errors::RuntimeError) override;

  Number* subInt(IntNumber* obj) throw(Errors::RuntimeError) override;

  Number* subFloat(FloatNumber* obj) throw(Errors::RuntimeError) override;

  Number* mul(Number* obj) throw(Errors::RuntimeError) override;

  Number* mulInt(IntNumber* obj) throw(Errors::RuntimeError) override;

  Number* mulFloat(FloatNumber* obj) throw(Errors::RuntimeError) override;

  Number* div(Number* obj) throw(Errors::RuntimeError) override;

  Number* divInt(IntNumber* obj) throw(Errors::RuntimeError) override;

  Number* divFloat(FloatNumber* obj) throw(Errors::RuntimeError) override;

  Number* remainder(Number* obj) throw(Errors::RuntimeError) override;

  Number* remainderInt(IntNumber* obj) throw(Errors::RuntimeError) override;

  Number* remainderFloat(FloatNumber* obj) throw(Errors::RuntimeError) override;

  std::string toString() const override;

 private:
  double value;
};
}

#endif // LISPINO_FLOATNUMBER_H_
