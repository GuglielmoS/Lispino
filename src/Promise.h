#ifndef LISPINO_PROMISE_H_
#define LISPINO_PROMISE_H_

#include <memory>

#include "Object.h"
#include "Environment.h"

namespace Lispino {

class Promise : public Object {
 public:
  Promise();

  void setBody(Object* body);

  void setCachedResult(Object* result);

  void setEnv(std::shared_ptr<Environment> env);

  Object* getBody();

  Object* getCachedResult();

  std::shared_ptr<Environment> getEnv();

  bool hasCachedResult() const;

  std::string toString() const override;

 private:
  Object *body;
  Object *result;
  bool cached_result_flag;
  std::shared_ptr<Environment> env;
};

}

#endif // LISPINO_PROMISE_H_
