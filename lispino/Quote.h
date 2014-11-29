#ifndef LISPINO_QUOTE_H_
#define LISPINO_QUOTE_H_

#include "Object.h"

namespace lispino {

class Environment;

class Quote : public Object {
 public:
  Quote();

  explicit Quote(Object* value);

  void setValue(Object* value);

  Object* getValue();

  std::string toString() const override;

 private:
  Object *value;
};
}

#endif  // LISPINO_QUOTE_H_
