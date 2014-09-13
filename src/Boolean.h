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

  Object* eval(Environment& env);

  int compare(Object* obj);

  int compareBoolean(Boolean* obj);

  bool isTrue() const;

  bool isFalse() const;

  bool isBoolean() const;

  std::string toString() const;

 private:
  // the value that the object represents
  bool value;
};

}

#endif // LISPINO_BOOLEAN_H_
