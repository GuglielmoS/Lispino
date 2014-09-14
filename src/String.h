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

  Object* eval(Environment& env);

  int compare(const Object* obj) const;

  int compareString(const String* obj) const;

  bool isAtom() const;

  bool isString() const;

  std::string toString() const;

 private:
  std::string value;
};

}

#endif // LISPINO_STRING_H_
