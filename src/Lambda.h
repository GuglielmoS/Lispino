#ifndef __LAMBDA_H__
#define __LAMBDA_H__

#include "Object.h"

#include <vector>
#include <string>

namespace Lispino {

    class Closure;

    class Lambda : public Object {

        Object *body;
        std::vector<std::string> arguments;

        public:

            Lambda() : body(nullptr) {}
            Lambda(Object* body, std::vector<std::string> arguments) :
                body(body), arguments(arguments) {}

            Object* eval(Environment& env);

            void setBody(Object* body) {
                this->body = body;
            }

            void setArguments(std::vector<std::string> arguments) {
                this->arguments = arguments;
            }

            std::vector<std::string> getArguments() const {
                return arguments;
            }

            Object* getBody() {
                return body;
            }

            bool isLambda() const {
                return true;
            }

            std::string toString() const {
                return "LAMBDA";
            }

    };
};

#endif // __LAMBDA_H__
