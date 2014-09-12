#ifndef LISPINO_CLOSURE_H_
#define LISPINO_CLOSURE_H_

#include <vector>
#include <memory>

#include "Object.h"
#include "Lambda.h"
#include "Environment.h"

namespace Lispino {

    class Closure : public Object {
        public:

            Closure();
            Closure(Lambda *lambda, Environment *parentEnv);

            Object* eval(Environment& env);
            Object* apply(std::vector<Object*>& actualArgs);

            void setLambda(Lambda *lambda);
            void setEnv(Environment *parentEnv);

            Environment* getEnv();

            void mark();

            bool isClosure() const;

            std::string toString() const;

        private:

            Lambda *lambda;
            std::unique_ptr<Environment> env;
    };
};

#endif // LISPINO_CLOSURE_H_
