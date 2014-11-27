#ifndef LISPINO_LAMBDA_H_
#define LISPINO_LAMBDA_H_

#include <cstdint>

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

  void setCatchRestFlag(bool catch_rest_flag);

  Object* getBody();

  std::vector<std::string> getArguments() const;

  std::uint32_t getRequiredArguments() const;

  bool hasCatchRest() const;

  std::string toString() const override;

 private:
  Object *body;

  std::vector<std::string> arguments;

  bool catch_rest_flag;
};

}

#endif // LISPINO_LAMBDA_H_
