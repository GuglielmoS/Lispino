#ifndef LISPINO_BOOLEAN_H_
#define LISPINO_BOOLEAN_H_

#include "Object.h"

namespace Lispino {

class Boolean : public Object {
 public:
  Boolean();

  explicit Boolean(bool value);

  void setValue(bool value);

  bool getValue() const;

  int compare(const Object* obj) const throw(Errors::RuntimeError) override;

  int compareBoolean(const Boolean* obj) const throw(Errors::RuntimeError) override;

  bool isTrue() const override;

  bool isFalse() const override;

  std::string toString() const override;

 private:
  // the value that the object represents
  bool value;
};
}

#endif // LISPINO_BOOLEAN_H_
