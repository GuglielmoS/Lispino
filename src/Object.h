#ifndef LISPINO_OBJECT_H_
#define LISPINO_OBJECT_H_

#include <string>
#include <stdexcept>

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
  SEQUENCE
};

class Object {
 public:
  Object();

  virtual ~Object();

  /// evaluate the object in the global environment
  Object* eval();

  /// evaluates the object accordingly to the provided environment
  virtual Object* eval(Environment& env) = 0;

  /*
  * Equality
  */

  virtual int compare(Object* obj);
  
  virtual int compareNil(Nil* obj);
  
  virtual int compareList(List* obj);
  
  virtual int compareInt(IntNumber* obj);
  
  virtual int compareFloat(FloatNumber* obj);
  
  virtual int compareSymbol(Symbol* obj);
  
  virtual int compareString(String* obj);
  
  virtual int compareBoolean(Boolean* obj);
  
  virtual int compareSequence(Sequence* obj);

  /*
  * Commoin operations between objects
  */

  virtual Object* negate();

  virtual Object* add(Object* obj);
  
  virtual Object* addInt(IntNumber* obj);
  
  virtual Object* addFloat(FloatNumber* obj);
  
  virtual Object* addString(String* obj);
  
  virtual Object* sub(Object* obj);
  
  virtual Object* subInt(IntNumber* obj);
  
  virtual Object* subFloat(FloatNumber* obj);

  virtual Object* mul(Object* obj);  

  virtual Object* mulInt(IntNumber* obj);
  
  virtual Object* mulFloat(FloatNumber* obj);
  
  virtual Object* div(Object* obj);
  
  virtual Object* divInt(IntNumber* obj);
  
  virtual Object* divFloat(FloatNumber* obj);  
  
  virtual Object* remainder(Object* obj);
  
  virtual Object* remainderInt(IntNumber* obj);
  
  virtual Object* remainderFloat(FloatNumber* obj);

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
  // flag used for the garbage collection
  bool markFlag;
};

}

#endif // LISPINO_OBJECT_H_
