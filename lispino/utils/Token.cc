#include "Token.h"

#include <cassert>

namespace lispino {

namespace utils {

std::string type2str(TokenType type) {
  switch (type) {
    case TokenType::EOS:          return "EOS";
    case TokenType::OPEN_PAREN:   return "'('";
    case TokenType::CLOSE_PAREN:  return "')'";
    case TokenType::DOT:          return "'.'";
    case TokenType::SMART_QUOTE:  return "'\''";
    case TokenType::CHARACTER:    return "#<CHARACTER>";
    case TokenType::SYMBOL:       return "#<SYMBOL>";
    case TokenType::INT_NUMBER:   return "#<INT_NUMBER>";
    case TokenType::FLOAT_NUMBER: return "#<FLOAT_NUMBER>";
    case TokenType::STRING:       return "#<STRING>";
    case TokenType::NIL:          return "NIL";
    case TokenType::LAMBDA:       return "LAMBDA";
    case TokenType::LET:          return "LET";
    case TokenType::DEFINE:       return "DEFINE";
    case TokenType::QUOTE:        return "QUOTE";
    case TokenType::IF:           return "IF";
    case TokenType::BOOL_FALSE:   return "#f";
    case TokenType::BOOL_TRUE:    return "#t";
    case TokenType::COND:         return "COND";
    case TokenType::BEGIN:        return "BEGIN";
    case TokenType::UNKNOWN:      return "UNKNOWN";

    // invalid token
    default:
      assert(false && "Cannot find the string for this token type!");
  }
}
}
}
