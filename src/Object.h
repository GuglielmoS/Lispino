#ifndef LISPINO_OBJECT_H_
#define LISPINO_OBJECT_H_

#include <string>

#include "errors/RuntimeError.h"

namespace Lispino {

class Environment;
class IntNumber;
class FloatNumber;
class Symbol;
class String;
class Boolean;
class Nil;
class List;
class Sequence;

enum class ObjectType {
  NIL,
  DEFINE,
  QUOTE,
  LIST,
  SYMBOL,
  STRING,
  INT_NUMBER, FLOAT_NUMBER,
  BOOLEAN,
  IF,
  LAMBDA,
  CLOSURE,
  SEQUENCE,
  BUILTIN_FUNCTION
};

class Object {
 public:
  Object(ObjectType type);

  virtual ~Object();

  ObjectType getType() const;

  /// evaluate the object in the global environment
  Object* eval() throw (Errors::RuntimeError);

  /// evaluates the object accordingly to the provided environment
  virtual Object* eval(Environment* env) throw (Errors::RuntimeError) = 0;

  /*
   * Equality
   */

  virtual int compare(const Object* obj) const throw (Errors::RuntimeError);
  
  virtual int compareNil(const Nil* obj) const throw (Errors::RuntimeError);
  
  virtual int compareList(const List* obj) const throw (Errors::RuntimeError);
  
  virtual int compareInt(const IntNumber* obj) const throw (Errors::RuntimeError);
  
  virtual int compareFloat(const FloatNumber* obj) const throw (Errors::RuntimeError);
  
  virtual int compareSymbol(const Symbol* obj) const throw (Errors::RuntimeError);
  
  virtual int compareString(const String* obj) const throw (Errors::RuntimeError);
  
  virtual int compareBoolean(const Boolean* obj) const throw (Errors::RuntimeError);
  
  virtual int compareSequence(const Sequence* obj) const throw (Errors::RuntimeError);

  /*
   * Common operations between objects
   */

  virtual Object* negate() throw (Errors::RuntimeError);

  virtual Object* add(Object* obj) throw (Errors::RuntimeError);
  
  virtual Object* addInt(IntNumber* obj) throw (Errors::RuntimeError);
  
  virtual Object* addFloat(FloatNumber* obj) throw (Errors::RuntimeError);
  
  virtual Object* addString(String* obj) throw (Errors::RuntimeError);
  
  virtual Object* sub(Object* obj) throw (Errors::RuntimeError);
  
  virtual Object* subInt(IntNumber* obj) throw (Errors::RuntimeError);
  
  virtual Object* subFloat(FloatNumber* obj) throw (Errors::RuntimeError);

  virtual Object* mul(Object* obj) throw (Errors::RuntimeError);  

  virtual Object* mulInt(IntNumber* obj) throw (Errors::RuntimeError);
  
  virtual Object* mulFloat(FloatNumber* obj) throw (Errors::RuntimeError);
  
  virtual Object* div(Object* obj) throw (Errors::RuntimeError);
  
  virtual Object* divInt(IntNumber* obj) throw (Errors::RuntimeError);
  
  virtual Object* divFloat(FloatNumber* obj) throw (Errors::RuntimeError); 
  
  virtual Object* remainder(Object* obj) throw (Errors::RuntimeError);
  
  virtual Object* remainderInt(IntNumber* obj) throw (Errors::RuntimeError);
  
  virtual Object* remainderFloat(FloatNumber* obj) throw (Errors::RuntimeError);

  /*
   * Garbage collection related methods 
   */

  // this is virtual because it's easier to recursively
  // mark objects by overriding this method
  virtual void mark();
  
  void unmark(); 

  bool isMarked() const;

  /*
   * Useful methods 
   */

  virtual bool isNil() const;
  
  virtual bool isAtom() const;
  
  virtual bool isList() const;
  
  virtual bool isLambda() const;
  
  virtual bool isClosure() const;
  
  virtual bool isIntNumber() const;
  
  virtual bool isFloatNumber() const;
  
  virtual bool isBoolean() const;
  
  virtual bool isSymbol() const;
  
  virtual bool isString() const;
  
  virtual bool isQuote() const;
  
  virtual bool isDefine() const;
  
  virtual bool isIfExpr() const;
  
  virtual bool isBuiltinFunction() const;
  
  virtual bool isSequence() const;

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
