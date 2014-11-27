#ifndef LISPINO_ARGS_H_
#define LISPINO_ARGS_H_

#include <vector>
#include <string>

#include "Object.h"
#include "List.h"
#include "Symbol.h"

namespace Lispino {

class Args {
 public:
  Args(std::vector<Object*> arguments, std::vector<Symbol*> arguments_names);

  Args(std::vector<Object*> arguments, std::vector<Symbol*> arguments_names, List* catch_rest);

  void setArguments(std::vector<Object*> arguments);

  void setArgumentsNames(std::vector<Symbol*> arguments_names);

  void setCatchRest(List* catch_rest);

  std::vector<Object*> getArguments() const;

  std::vector<Symbol*> getArgumentsNames() const;

  List* getCatchRest();

  bool hasCatchRest() const;

 private:
  std::vector<Object*> arguments;
  std::vector<Symbol*> arguments_names;
  List *catch_rest;
};
}

#endif // LISPINO_ARGS_H_
