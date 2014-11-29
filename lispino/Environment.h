#ifndef LISPINO_ENVIRONMENT_H_
#define LISPINO_ENVIRONMENT_H_

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <utility>
#include <map>
#include <unordered_map>

#include "Object.h"
#include "Symbol.h"
#include "Args.h"
#include "builtins/BuiltinFunction.h"
#include "errors/RuntimeError.h"

namespace lispino {

typedef std::unordered_map<std::string, std::pair<Symbol*, Object*>> LookupTable;
typedef std::unordered_map<std::string, std::unique_ptr<builtins::BuiltinFunction>> BuiltinsTable;

class Environment {
 public:
  Environment();

  void setParent(std::shared_ptr<Environment> env);

  std::shared_ptr<Environment> getParent() const;

  LookupTable& getLookupTable();

  Object* update(Symbol* key, Object* value) throw(errors::RuntimeError);
  Object* put(Symbol* key, Object* value);
  Object* get(Symbol* key) throw(errors::RuntimeError);

  void applyArgs(Args& arguments);

  static std::shared_ptr<Environment> extend(std::shared_ptr<Environment> env);

 private:
  std::shared_ptr<Environment> parent;
  LookupTable frame;

  // builtin functions
  static BuiltinsTable builtin_functions;
  static BuiltinsTable initializeBuiltinFunctions();
  static void bind(BuiltinsTable& bindings, builtins::BuiltinFunction *fun);
};
}

#endif  // LISPINO_ENVIRONMENT_H_
