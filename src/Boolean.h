#ifndef LISPINO_BOOLEAN_H_
#define LISPINO_BOOLEAN_H_

#include "Object.h"

namespace Lispino {

class Boolean : public Object {
 public:
  Boolean();

  Boolean(bool value);

  void setValue(bool value);

  bool getValue() const;

  Object* eval(Environment* env) override;

  int compare(const Object* obj) const override;

  int compareBoolean(const Boolean* obj) const override;

  bool isTrue() const;

  bool isFalse() const;

  bool isBoolean() const override;

  std::string toString() const override;

 private:
  // the value that the object represents
  bool value;
};

}

#endif // LISPINO_BOOLEAN_H_
