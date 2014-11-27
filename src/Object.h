#ifndef LISPINO_OBJECT_H_
#define LISPINO_OBJECT_H_

#include <string>
#include <memory>

#include "errors/RuntimeError.h"

namespace Lispino {

class Environment;
class IntNumber;
class FloatNumber;
class Symbol;
class Character;
class String;
class Boolean;
class Nil;
class List;
class Sequence;
class Promise;

enum class ObjectType {
  NIL,
  DEFINE,
  QUOTE,
  LIST,
  SYMBOL,
  CHARACTER,
  STRING,
  INT_NUMBER, FLOAT_NUMBER,
  BOOLEAN,
  IF,
  LAMBDA,
  CLOSURE,
  PROMISE,
  SEQUENCE,
  BUILTIN_FUNCTION
};

class Object {
 public:
  explicit Object(ObjectType type);

  virtual ~Object();

  inline ObjectType getType() const {
    return type;
  }

  /*
   * Equality
   */

  // EQ?

  inline bool eq(const Object* obj) const {
    return this == obj;
  }

  // EQV?

  virtual bool eqv(const Object* obj) const;

  virtual bool eqvInt(const IntNumber* obj) const;

  virtual bool eqvFloat(const FloatNumber* obj) const;

  virtual bool eqvCharacter(const Character* obj) const;

  // EQUAL?

  virtual bool equal(const Object* obj) const;

  virtual bool equalString(const String* obj) const;

  virtual bool equalList(const List* obj) const;

  // COMPARE FOR =, >, >=, <, <=

  virtual int compare(const Object* obj) const throw(Errors::RuntimeError);

  virtual int compareNil(const Nil* obj) const throw(Errors::RuntimeError);

  virtual int compareList(const List* obj) const throw(Errors::RuntimeError);

  virtual int compareInt(const IntNumber* obj) const throw(Errors::RuntimeError);

  virtual int compareFloat(const FloatNumber* obj) const throw(Errors::RuntimeError);

  virtual int compareSymbol(const Symbol* obj) const throw(Errors::RuntimeError);

  virtual int compareCharacter(const Character* obj) const throw(Errors::RuntimeError);

  virtual int compareString(const String* obj) const throw(Errors::RuntimeError);

  virtual int compareBoolean(const Boolean* obj) const throw(Errors::RuntimeError);

  /*
   * Garbage collection related methods 
   */

  inline void mark() {
    markFlag = true;
  }

  inline void unmark() {
    markFlag = false;
  }

  inline bool isMarked() const {
    return markFlag;
  }

  /*
   * Useful methods 
   */

  virtual bool isTrue() const;

  virtual bool isFalse() const;

  inline bool isNil() const {
    return type == ObjectType::NIL;
  }

  inline bool isList() const {
    return type == ObjectType::LIST;
  }

  inline bool isLambda() const {
    return type == ObjectType::LAMBDA;
  }

  inline bool isClosure() const {
    return type == ObjectType::CLOSURE;
  }

  inline bool isPromise() const {
    return type == ObjectType::PROMISE;
  }

  inline bool isNumber() const {
    return isIntNumber() || isFloatNumber();
  }

  inline bool isIntNumber() const {
    return type == ObjectType::INT_NUMBER;
  }

  inline bool isFloatNumber() const {
    return type == ObjectType::FLOAT_NUMBER;
  }

  inline bool isBoolean() const {
    return type == ObjectType::BOOLEAN;
  }

  inline bool isSymbol() const {
    return type == ObjectType::SYMBOL;
  }

  inline bool isCharacter() const {
    return type == ObjectType::CHARACTER;
  }

  inline bool isString() const {
    return type == ObjectType::STRING;
  }

  inline bool isQuote() const {
    return type == ObjectType::QUOTE;
  }

  inline bool isDefine() const {
    return type == ObjectType::DEFINE;
  }

  inline bool isIfExpr() const {
    return type == ObjectType::IF;
  }

  inline bool isBuiltinFunction() const {
    return type == ObjectType::BUILTIN_FUNCTION;
  }

  inline bool isSequence() const {
    return type == ObjectType::SEQUENCE;
  }

  /// provides a string representation of the object
  virtual std::string toString() const = 0;

 private:
  // type used for the evaluation
  ObjectType type;

  // flag used for the garbage collection
  bool markFlag;
};
}

#endif // LISPINO_OBJECT_H_
