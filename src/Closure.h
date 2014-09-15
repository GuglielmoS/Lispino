#ifndef LISPINO_CLOSURE_H_
#define LISPINO_CLOSURE_H_

#include <memory>

#include "Object.h"
#include "Lambda.h"
#include "Environment.h"

namespace Lispino {

class Closure : public Object {
 public:
  Closure();

  Closure(Lambda *lambda, Environment *env);

  void setLambda(Lambda *lambda);

  void setEnv(Environment *env);

  Lambda* getLambda();

  Environment* getEnv();

  Object* eval(Environment* env) override;

  void mark() override;

  bool isClosure() const override;

  std::string toString() const override;

 private:
  Lambda *lambda;
  std::unique_ptr<Environment> env;
};

}

#endif // LISPINO_CLOSURE_H_
