#ifndef LISPINO_NUMBER_H_
#define LISPINO_NUMBER_H_

#include "Object.h"

namespace Lispino {

class Number : public Object {
 public:
  explicit Number(ObjectType type);

  virtual Object* negate() throw(Errors::RuntimeError) = 0;

  virtual Number* add(Number* obj) throw(Errors::RuntimeError) = 0;

  virtual Number* addInt(IntNumber* obj) throw(Errors::RuntimeError) = 0;

  virtual Number* addFloat(FloatNumber* obj) throw(Errors::RuntimeError) = 0;

  virtual Number* sub(Number* obj) throw(Errors::RuntimeError) = 0;

  virtual Number* subInt(IntNumber* obj) throw(Errors::RuntimeError) = 0;

  virtual Number* subFloat(FloatNumber* obj) throw(Errors::RuntimeError) = 0;

  virtual Number* mul(Number* obj) throw(Errors::RuntimeError) = 0;

  virtual Number* mulInt(IntNumber* obj) throw(Errors::RuntimeError) = 0;

  virtual Number* mulFloat(FloatNumber* obj) throw(Errors::RuntimeError) = 0;

  virtual Number* div(Number* obj) throw(Errors::RuntimeError) = 0;

  virtual Number* divInt(IntNumber* obj) throw(Errors::RuntimeError) = 0;

  virtual Number* divFloat(FloatNumber* obj) throw(Errors::RuntimeError) = 0;

  virtual Number* remainder(Number* obj) throw(Errors::RuntimeError) = 0;

  virtual Number* remainderInt(IntNumber* obj) throw(Errors::RuntimeError) = 0;

  virtual Number* remainderFloat(FloatNumber* obj) throw(Errors::RuntimeError) = 0;
};
}

#endif // LISPINO_NUMBER_H_
