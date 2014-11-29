#ifndef LISPINO_SEQUENCE_H_
#define LISPINO_SEQUENCE_H_

#include <vector>

#include "Object.h"

namespace lispino {

class Sequence : public Object {
 public:
  Sequence();

  void setValue(std::vector<Object*> value);

  std::vector<Object*>& getValue();

  std::string toString() const override;

 private:
  std::vector<Object*> expressions;
};
}

#endif // LISPINO_SEQUENCE_H_
