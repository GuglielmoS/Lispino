#include "Object.h"

#include <cassert>

namespace lispino {

namespace utils {

std::string objtype2str(ObjectType type) {
  switch (type) {
    case ObjectType::NIL:              return "#<NIL>";
    case ObjectType::DEFINE:           return "#<DEFINE>";
    case ObjectType::QUOTE:            return "#<QUOTE>";
    case ObjectType::LIST:             return "#<LIST>";
    case ObjectType::SYMBOL:           return "#<SYMBOL>";
    case ObjectType::CHARACTER:        return "#<CHARACTER>";
    case ObjectType::STRING:           return "#<STRING>";
    case ObjectType::INT_NUMBER:       return "#<INT_NUMBER>";
    case ObjectType::FLOAT_NUMBER:     return "#<FLOAT_NUMBER>";
    case ObjectType::BOOLEAN:          return "#<BOOLEAN>";
    case ObjectType::IF:               return "#<IF>";
    case ObjectType::LAMBDA:           return "#<LAMBDA>";
    case ObjectType::CLOSURE:          return "#<CLOSURE>";
    case ObjectType::PROMISE:          return "#<PROMISE>";
    case ObjectType::SEQUENCE:         return "#<SEQUENCE>";
    case ObjectType::BUILTIN_FUNCTION: return "<#BUILTIN_FUNCTION>";

    // invalid object
    default:
      assert(false && "Cannot find the string for this object type!");
  }
}
}
}
