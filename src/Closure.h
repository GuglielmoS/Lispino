#ifndef LISPINO_CLOSURE_H_
#define LISPINO_CLOSURE_H_

#include <vector>
#include <memory>

#include "Object.h"
#include "Lambda.h"
#include "Environment.h"

namespace Lispino {

    class Closure : public Object {
        Lambda *lambda;
        std::unique_ptr<Environment> env;

        public:

            Closure() : lambda(nullptr), env(nullptr) {}
            Closure(Lambda *lambda, Environment *parentEnv) : lambda(lambda), env(new Environment(parentEnv)) {}

            Object* eval(Environment& env) {
                return this;
            }

            Object* apply(std::vector<Object*>& actualArgs);

            bool equals(Object *obj) const {
                // Two closure are never equals.
                // only when the pointers have the same address
                // we can return true
                return obj == this;
            }

            void setLambda(Lambda *lambda) {
                this->lambda = lambda;
            }

            void setEnv(Environment *parentEnv) {
                this->env.reset(new Environment(parentEnv));
            }

            Environment* getEnv() {
                return env.get();
            }

            void mark() {
                Object::mark();
                lambda->mark();
            }

            bool isClosure() const {
                return true;
            }

            std::string toString() const {
                return "CLOSURE";
            }
    };
};

#endif // LISPINO_CLOSURE_H_
