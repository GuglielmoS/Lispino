#ifndef LISPINO_SYMBOL_H_
#define LISPINO_SYMBOL_H_

#include <string>

#include "Object.h"

namespace Lispino {

class Symbol : public Object {
 public:
  Symbol();

  Symbol(std::string value);

  void setValue(std::string value);
  
  std::string getValue() const;

  Object* eval(Environment* env) throw (Errors::RuntimeError) override;

  int compare(const Object* obj) const override;
  
  int compareSymbol(const Symbol* obj) const override;

  bool isAtom() const override;

  bool isSymbol() const override;

  std::string toString() const override;

 private:
  std::string value;
};

}

#endif // LISPINO_SYMBOL_H_
