#ifndef LISPINO_STRING_H_
#define LISPINO_STRING_H_

#include <sstream>
#include <string>

#include "Object.h"

namespace Lispino {

class String : public Object {
 public:
  String();

  String(std::string value);

  void setValue(std::string value);

  std::string getValue() const;

  Object* eval(Environment* env) override;

  int compare(const Object* obj) const override;

  int compareString(const String* obj) const override;

  bool isAtom() const override;

  bool isString() const override;

  std::string toString() const override;

 private:
  std::string value;
};

}

#endif // LISPINO_STRING_H_
