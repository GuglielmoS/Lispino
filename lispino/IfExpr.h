#ifndef LISPINO_IFEXPR_H_
#define LISPINO_IFEXPR_H_

#include <string>

#include "Object.h"

namespace lispino {

class IfExpr : public Object {
 public:
  IfExpr();

  void setCondition(Object* condition);

  void setConsequent(Object* consequent);

  void setAlternative(Object* alternative);

  Object* getCondition();

  Object* getConsequent();

  Object* getAlternative();

  std::string toString() const override;

 private:
  Object *condition;
  Object *consequent;
  Object *alternative;
};
}

#endif  // LISPINO_IFEXPR_H_
