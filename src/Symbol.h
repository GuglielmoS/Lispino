#ifndef LISPINO_SYMBOL_H_
#define LISPINO_SYMBOL_H_

#include <string>

#include "Object.h"

namespace Lispino {

class Symbol : public Object {
 public:
  Symbol();

  explicit Symbol(std::string value);

  void setValue(std::string value);

  std::string getValue() const;

  int compare(const Object* obj) const throw(Errors::RuntimeError) override;

  int compareSymbol(const Symbol* obj) const throw(Errors::RuntimeError) override;

  std::string toString() const override;

 private:
  std::string value;
};
}

#endif // LISPINO_SYMBOL_H_
