#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>

namespace Lispino {

    class Environment;

    class Object {
        
        // flag used for garbage collection
        bool markFlag;

        public:

            enum ObjectType {
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
                CLOSURE
            };

            Object() : markFlag(false) {}

            // evaluate the object in the global environment
            Object* eval();

            /*
             * Abstract methods
             */

            /// evaluates the object accordingly to the provided environment
            virtual Object* eval(Environment& env) = 0;

            /// compares the current object with another one
            virtual bool equals(Object *obj) const {
                return this == obj;
            }

            /// provides a string representation for the object
            virtual std::string toString() const = 0;

            /// default destructor
            virtual ~Object() { /* DO NOTHING */ }

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

            virtual bool isNil() const {
                return false;
            }

            virtual bool isAtom() const {
                return false;
            }

            virtual bool isList() const {
                return false;
            }

            virtual bool isLambda() const {
                return false;
            }

            virtual bool isClosure() const {
                return false;
            }

            virtual bool isIntNumber() const {
                return false;
            }

            virtual bool isFloatNumber() const {
                return false;
            }

            virtual bool isBoolean() const {
                return false;
            }

            virtual bool isSymbol() const {
                return false;
            }

            virtual bool isString() const {
                return false;
            }

            virtual bool isQuote() const {
                return false;
            }

            virtual bool isDefine() const {
                return false;
            }

            virtual bool isIfExpr() const {
                return false;
            }

            virtual bool isBuiltinFunction() const {
                return false;
            }

    };
};

#endif // __OBJECT_H__
