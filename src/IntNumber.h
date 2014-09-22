#ifndef LISPINO_INTNUMBER_H_
#define LISPINO_INTNUMBER_H_

#include <cstdint>

#include <string>

#include "Object.h"

namespace Lispino {

class IntNumber : public Object {
 public:
  IntNumber();

  IntNumber(std::int64_t value);

  void setValue(std::int64_t value);

  std::int64_t getValue() const;

  int compare(const Object* obj) const throw (Errors::RuntimeError) override;

  int compareInt(const IntNumber* obj) const throw (Errors::RuntimeError) override;

  int compareFloat(const FloatNumber* obj) const throw (Errors::RuntimeError) override;
  
  Object* negate() throw (Errors::RuntimeError) override;

  Object* add(Object* obj) throw (Errors::RuntimeError) override;

  Object* addInt(IntNumber* obj) throw (Errors::RuntimeError) override;

  Object* addFloat(FloatNumber* obj) throw (Errors::RuntimeError) override;

  Object* sub(Object* obj) throw (Errors::RuntimeError) override;
  
  Object* subInt(IntNumber* obj) throw (Errors::RuntimeError) override;
  
  Object* subFloat(FloatNumber* obj) throw (Errors::RuntimeError) override;
  
  Object* mul(Object* obj) throw (Errors::RuntimeError) override;
  
  Object* mulInt(IntNumber* obj) throw (Errors::RuntimeError) override;
  
  Object* mulFloat(FloatNumber* obj) throw (Errors::RuntimeError) override;
  
  Object* div(Object* obj) throw (Errors::RuntimeError) override;
  
  Object* divInt(IntNumber* obj) throw (Errors::RuntimeError) override;
  
  Object* divFloat(FloatNumber* obj) throw (Errors::RuntimeError) override;
  
  Object* remainder(Object* obj) throw (Errors::RuntimeError) override;
  
  Object* remainderInt(IntNumber* obj) throw (Errors::RuntimeError) override;

  std::string toString() const override;

 private:
  std::int32_t value;
};

}

#endif // LISPINO_INTNUMBER_H_
