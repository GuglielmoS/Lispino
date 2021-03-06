#ifndef LISPINO_CLOSURE_H_
#define LISPINO_CLOSURE_H_

#include <string>
#include <memory>

#include "Object.h"
#include "Lambda.h"
#include "Environment.h"

namespace lispino {

class Closure : public Object {
 public:
  Closure();

  void setLambda(Lambda *lambda);

  void setEnv(std::shared_ptr<Environment> env);

  Lambda* getLambda();

  std::shared_ptr<Environment> getEnv() const;

  std::string toString() const override;

 private:
  Lambda *lambda;
  std::shared_ptr<Environment> env;
};
}

#endif  // LISPINO_CLOSURE_H_
