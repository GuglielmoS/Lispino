#include "Read.h"

#include "../VM.h"
#include "../Parser.h"

namespace lispino {

namespace builtins {

std::uint32_t Read::getRequiredArguments() const {
  return 0;
}

std::string Read::getName() const {
  return "read";
}

Object* Read::apply(std::vector<Object*>&, std::shared_ptr<Environment>) throw(errors::RuntimeError) {
  std::string input_expr;

  // gets the expression
  std::getline(std::cin, input_expr);

  // evaluates the expression
  std::stringstream stream(input_expr);

  // try to parse the given expression
  Object *expr = Parser(stream).parse();
  if (expr == nullptr)
    expr = VM::getAllocator().createNil();

  return expr;
}
}
}
