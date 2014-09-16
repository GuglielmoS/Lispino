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

  Object* eval(Environment* env) throw (Errors::RuntimeError) override;

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

  Object* remainderFloat(FloatNumber* obj) throw (Errors::RuntimeError) override;

  bool isAtom() const override;

  bool isFloatNumber() const override;

  std::string toString() const override;

 private:
  double value;
};

}

#endif // LISPINO_FLOATNUMBER_H_
