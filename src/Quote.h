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

  Object* eval(Environment* env) override;

  void mark() override;

  bool isQuote() const override;

  std::string toString() const override;

 private:
  Object *value;
};

}

#endif // LISPINO_QUOTE_H_
