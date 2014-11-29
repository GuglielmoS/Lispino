#ifndef LISPINO_STRING_H_
#define LISPINO_STRING_H_

#include <sstream>
#include <string>

#include "Object.h"

namespace lispino {

class String : public Object {
 public:
  String();

  explicit String(std::string value);

  void setValue(std::string value);

  std::string getValue() const;

  bool equal(const Object* obj) const override;

  bool equalString(const String* obj) const override;

  int compare(const Object* obj) const throw(errors::RuntimeError) override;

  int compareString(const String* obj) const throw(errors::RuntimeError) override;

  std::string toString() const override;

 private:
  std::string value;

  std::string escape(std::string string) const;
};
}

#endif // LISPINO_STRING_H_
