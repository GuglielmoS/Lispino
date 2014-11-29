#ifndef LISPINO_FLOATNUMBER_H_
#define LISPINO_FLOATNUMBER_H_

#include <string>

#include "Number.h"

namespace lispino {

class FloatNumber : public Number {
 public:
  FloatNumber();

  explicit FloatNumber(double value);

  void setValue(double value);

  double getValue() const;

  bool eqv(const Object* obj) const override;

  bool eqvFloat(const FloatNumber* obj) const override;

  int compare(const Object* obj) const throw(errors::RuntimeError) override;

  int compareInt(const IntNumber* obj) const throw(errors::RuntimeError) override;

  int compareFloat(const FloatNumber* obj) const throw(errors::RuntimeError) override;

  Number* negate() throw(errors::RuntimeError) override;

  Number* add(Number* obj) throw(errors::RuntimeError) override;

  Number* addInt(IntNumber* obj) throw(errors::RuntimeError) override;

  Number* addFloat(FloatNumber* obj) throw(errors::RuntimeError) override;

  Number* sub(Number* obj) throw(errors::RuntimeError) override;

  Number* subInt(IntNumber* obj) throw(errors::RuntimeError) override;

  Number* subFloat(FloatNumber* obj) throw(errors::RuntimeError) override;

  Number* mul(Number* obj) throw(errors::RuntimeError) override;

  Number* mulInt(IntNumber* obj) throw(errors::RuntimeError) override;

  Number* mulFloat(FloatNumber* obj) throw(errors::RuntimeError) override;

  Number* div(Number* obj) throw(errors::RuntimeError) override;

  Number* divInt(IntNumber* obj) throw(errors::RuntimeError) override;

  Number* divFloat(FloatNumber* obj) throw(errors::RuntimeError) override;

  Number* remainder(Number* obj) throw(errors::RuntimeError) override;

  Number* remainderInt(IntNumber* obj) throw(errors::RuntimeError) override;

  Number* remainderFloat(FloatNumber* obj) throw(errors::RuntimeError) override;

  std::string toString() const override;

 private:
  double value;
};
}

#endif  // LISPINO_FLOATNUMBER_H_
