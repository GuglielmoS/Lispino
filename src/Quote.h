#ifndef LISPINO_QUOTE_H_
#define LISPINO_QUOTE_H_

#include "Object.h"

namespace Lispino {

class Environment;

class Quote : public Object {
 public:
  Quote();

  Quote(Object* value);

  void setValue(Object* value);
  
  Object* getValue();

  void mark() override;

  std::string toString() const override;

 private:
  Object *value;
};

}

#endif // LISPINO_QUOTE_H_
