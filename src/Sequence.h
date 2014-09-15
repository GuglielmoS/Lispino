#ifndef LISPINO_SEQUENCE_H_
#define LISPINO_SEQUENCE_H_

#include <vector>

#include "Object.h"

namespace Lispino {

class Sequence : public Object {
 public:
  void setValue(std::vector<Object*> value);

  std::vector<Object*>& getValue();

  Object* eval(Environment* env) override;

  void mark() override;

  bool isSequence() const override;

  std::string toString() const override;

 private:
  std::vector<Object*> expressions;
};

}

#endif // LISPINO_SEQUENCE_H_
