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
  
  std::string& getValue();

  Object* eval(Environment& env);

  int compare(Object* obj);
  
  int compareSymbol(Symbol* obj);

  bool isAtom() const;

  bool isSymbol() const;

  std::string toString() const;

 private:
  std::string value;
};

}

#endif // LISPINO_SYMBOL_H_
