#ifndef LISPINO_LAMBDA_H_
#define LISPINO_LAMBDA_H_

#include <vector>
#include <string>

#include "Object.h"
#include "Symbol.h"

namespace Lispino {

    class Closure;

    class Lambda : public Object {

        Object *body;
        std::vector<std::string> arguments;

        public:

            Lambda() : body(nullptr) {}
            Lambda(Object* body, std::vector<std::string> arguments) :
                body(body), arguments(arguments) {
            }

            Object* eval(Environment& env);

            void setBody(Object* body) {
                this->body = body;
            }

            void setArguments(std::vector<std::string> arguments);
            std::vector<std::string> getArguments();

            Object* getBody() {
                return body;
            }

            void mark() {
                Object::mark();
                body->mark();
            }

            bool isLambda() const {
                return true;
            }

            std::string toString() const {
                return "LAMBDA";
            }
    };
};

#endif // LISPINO_LAMBDA_H_
