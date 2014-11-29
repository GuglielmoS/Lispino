#ifndef LISPINO_INTNUMBER_H_
#define LISPINO_INTNUMBER_H_

#include <string>
#include <cstdint>

#include "Number.h"

namespace lispino {

class IntNumber : public Number {
 public:
  IntNumber();

  explicit IntNumber(std::int64_t value);

  void setValue(std::int64_t value);

  std::int64_t getValue() const;

  bool eqv(const Object* obj) const override;

  bool eqvInt(const IntNumber* obj) const override;

  int compare(const Object* obj) const throw(errors::RuntimeError) override;

  int compareInt(const IntNumber* obj) const throw(errors::RuntimeError) override;

  int compareFloat(const FloatNumber* obj) const throw(errors::RuntimeError) override;

  Object* negate() throw(errors::RuntimeError) override;

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

  Number* remainderFloat(FloatNumber* obj) throw(errors::RuntimeError);

  std::string toString() const override;

 private:
  std::int64_t value;
};
}

#endif  // LISPINO_INTNUMBER_H_
