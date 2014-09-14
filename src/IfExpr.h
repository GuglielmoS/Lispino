#ifndef LISPINO_IFEXPR_H_
#define LISPINO_IFEXPR_H_

#include "Object.h"

namespace Lispino {

class IfExpr : public Object {
 public:
  IfExpr();

  void setCondition(Object* condition);

  void setConsequent(Object* consequent);

  void setAlternative(Object* alternative);

  Object* getCondition();

  Object* getConsequent();

  Object* getAlternative();

  Object* eval(Environment* env);

  void mark();

  bool isIfExpr() const;

  std::string toString() const;

 private:

  Object *condition;
  Object *consequent;
  Object *alternative;
};

}

#endif // LISPINO_IFEXPR_H_
