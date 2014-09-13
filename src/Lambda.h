#ifndef LISPINO_LAMBDA_H_
#define LISPINO_LAMBDA_H_

#include <vector>
#include <string>

#include "Object.h"
#include "Symbol.h"

namespace Lispino {

class Closure;

class Lambda : public Object {
 public:
  Lambda();

  Lambda(Object* body, std::vector<std::string> arguments);

  void setBody(Object* body);

  void setArguments(std::vector<std::string> arguments);

  Object* getBody();

  std::vector<std::string> getArguments();

  Object* eval(Environment& env);

  void mark();

  bool isLambda() const;

  std::string toString() const;

 private:
  Object *body;
  std::vector<std::string> arguments;
};

}

#endif // LISPINO_LAMBDA_H_
