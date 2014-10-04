#ifndef LISPINO_INTNUMBER_H_
#define LISPINO_INTNUMBER_H_

#include <cstdint>

#include "Number.h"

namespace Lispino {

class IntNumber : public Number {
 public:
  IntNumber();

  IntNumber(std::int64_t value);

  void setValue(std::int64_t value);

  std::int64_t getValue() const;

  bool eqv(const Object* obj) const override;

  bool eqvInt(const IntNumber* obj) const override;

  int compare(const Object* obj) const throw (Errors::RuntimeError) override;

  int compareInt(const IntNumber* obj) const throw (Errors::RuntimeError) override;

  int compareFloat(const FloatNumber* obj) const throw (Errors::RuntimeError) override;
  
  Object* negate() throw (Errors::RuntimeError) override;

  Number* add(Number* obj) throw (Errors::RuntimeError) override;

  Number* addInt(IntNumber* obj) throw (Errors::RuntimeError) override;

  Number* addFloat(FloatNumber* obj) throw (Errors::RuntimeError) override;

  Number* sub(Number* obj) throw (Errors::RuntimeError) override;
  
  Number* subInt(IntNumber* obj) throw (Errors::RuntimeError) override;
  
  Number* subFloat(FloatNumber* obj) throw (Errors::RuntimeError) override;
  
  Number* mul(Number* obj) throw (Errors::RuntimeError) override;
  
  Number* mulInt(IntNumber* obj) throw (Errors::RuntimeError) override;
  
  Number* mulFloat(FloatNumber* obj) throw (Errors::RuntimeError) override;
  
  Number* div(Number* obj) throw (Errors::RuntimeError) override;
  
  Number* divInt(IntNumber* obj) throw (Errors::RuntimeError) override;
  
  Number* divFloat(FloatNumber* obj) throw (Errors::RuntimeError) override;
  
  Number* remainder(Number* obj) throw (Errors::RuntimeError) override;

  Number* remainderInt(IntNumber* obj) throw (Errors::RuntimeError) override;

  Number* remainderFloat(FloatNumber* obj) throw (Errors::RuntimeError);

  std::string toString() const override;

 private:
  std::int32_t value;
};

}

#endif // LISPINO_INTNUMBER_H_
