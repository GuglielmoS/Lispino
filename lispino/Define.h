#ifndef LISPINO_DEFINE_H_
#define LISPINO_DEFINE_H_

#include <string>

#include "Object.h"
#include "Symbol.h"

namespace lispino {

class Environment;

class Define : public Object {
 public:
  Define();

  Define(Symbol* name, Object* value);

  void setName(Symbol* name);

  void setValue(Object* value);

  std::string getName() const;

  Symbol* getSymbol();

  Object* getValue();

  std::string toString() const override;

 private:
  Symbol *name;
  Object *value;
};
}

#endif  // LISPINO_DEFINE_H_
