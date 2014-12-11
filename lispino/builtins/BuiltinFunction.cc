#include "BuiltinFunction.h"

#include <sstream>

#include "../VM.h"
#include "../utils/Object.h"

namespace lispino {

namespace builtins {

BuiltinFunction::BuiltinFunction() : 
    Object(ObjectType::BUILTIN_FUNCTION),
    lazyEvalFlag(false) {
  /* DO NOTHING */    
}

BuiltinFunction::BuiltinFunction(bool lazyEvalFlag) : 
    Object(ObjectType::BUILTIN_FUNCTION),
    lazyEvalFlag(lazyEvalFlag) {
  /* DO NOTHING */    
}

bool BuiltinFunction::isLazy() const {
  return lazyEvalFlag;
}

bool BuiltinFunction::hasExactArguments() const {
  return true;
}

std::string BuiltinFunction::toString() const {
  return "#<BUILTIN-FUNCTION:" + getName() + ">";
}

void BuiltinFunction::check(Object *object, ObjectType expected_type) const throw(errors::RuntimeError) {
  if (object->getType() != expected_type) {
    std::stringstream buf;
    buf << "expected " << utils::objtype2str(expected_type) << ", "
        << "found " << utils::objtype2str(object->getType());
    throw errors::RuntimeError(getName() + ": " + buf.str());
  }
}

void BuiltinFunction::check(Object *object, std::initializer_list<ObjectType> expected_types) const throw(errors::RuntimeError) {
  // check for one of the expected types
  for (auto const& type : expected_types) {
    if (object->getType() == type)
      return;
  }

  // since we are here, the object is invalid
  std::stringstream buf;
  bool multiple_types = false;
  auto size = expected_types.size();
  if (size > 1)
    multiple_types = true;

  buf << "expected ";
  auto iter = expected_types.begin();
  for (; iter != expected_types.end()-1; iter++) {
    buf << utils::objtype2str(*iter);
    if (multiple_types)
      buf << " or ";
  }

  if (multiple_types)
    buf << utils::objtype2str(*(expected_types.end()-1));

  buf << ", found " << utils::objtype2str(object->getType());

  throw errors::RuntimeError(getName() + ": " + buf.str());
}
}
}
