#ifndef LISPINO_ENVIRONMENT_H_
#define LISPINO_ENVIRONMENT_H_

#include <map>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iostream>
#include <memory>

#include "Object.h"
#include "Symbol.h"
#include "builtins/BuiltinFunction.h"

namespace Lispino {

class Environment {   
 public:

  Environment();

  Environment(Environment* env);

  Environment* getParent();

  void setParent(Environment *env);

  std::unordered_map<std::string, std::pair<Symbol*, Object*>>& lookupTable();

  Object* update(Symbol* key, Object* value);
  Object* put(Symbol* key, Object* value);
  Object* get(Symbol* key);

 private:

  Environment *parent;
  std::unordered_map<std::string, std::pair<Symbol*, Object*>> frame;

  // builtin functions
  static std::unordered_map<std::string, std::unique_ptr<Builtins::BuiltinFunction>> builtin_functions;
  static std::unordered_map<std::string, std::unique_ptr<Builtins::BuiltinFunction>> initializeBuiltinFunctions();
};

}

#endif // LISPINO_ENVIRONMENT_H_
