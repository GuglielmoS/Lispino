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

typedef std::unordered_map<std::string, std::pair<Symbol*, Object*>> LookupTable;
typedef std::unordered_map<std::string, std::unique_ptr<Builtins::BuiltinFunction>> BuiltinsTable; 

class Environment {   
 public:
  Environment();

  void setParent(Environment *env);

  Environment* getParent();

  Environment* extend();

  LookupTable& getLookupTable();

  Object* update(Symbol* key, Object* value);
  Object* put(Symbol* key, Object* value);
  Object* get(Symbol* key);

 private:
  Environment *parent;
  LookupTable frame;

  // builtin functions
  static BuiltinsTable builtin_functions;
  static BuiltinsTable initializeBuiltinFunctions();
};

}

#endif // LISPINO_ENVIRONMENT_H_
