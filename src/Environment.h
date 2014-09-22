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
#include "errors/RuntimeError.h"

namespace Lispino {

typedef std::unordered_map<std::string, std::pair<Symbol*, Object*>> LookupTable;
typedef std::unordered_map<std::string, std::unique_ptr<Builtins::BuiltinFunction>> BuiltinsTable; 

class Environment {   
 public:
  Environment();

  void setParent(std::shared_ptr<Environment> env);

  std::shared_ptr<Environment> getParent();

  LookupTable& getLookupTable();

  Object* update(Symbol* key, Object* value) throw (Errors::RuntimeError);
  Object* put(Symbol* key, Object* value);
  Object* get(Symbol* key) throw (Errors::RuntimeError);

  static std::shared_ptr<Environment> extend(std::shared_ptr<Environment> env);

 private:
  std::shared_ptr<Environment> parent;
  LookupTable frame;

  // builtin functions
  static BuiltinsTable builtin_functions;
  static BuiltinsTable initializeBuiltinFunctions();
  static void bind(BuiltinsTable& bindings, Builtins::BuiltinFunction *fun);
};

}

#endif // LISPINO_ENVIRONMENT_H_
