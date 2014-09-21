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

  void setLambda(Lambda *lambda);

  void setEnv(std::shared_ptr<Environment> env);

  Lambda* getLambda();

  std::shared_ptr<Environment> getEnv();

  Object* eval(Environment* env) throw (Errors::RuntimeError) override;

  void mark() override;

  bool isClosure() const override;

  std::string toString() const override;

 private:
  Lambda *lambda;
  std::shared_ptr<Environment> env;
};

}

#endif // LISPINO_CLOSURE_H_
