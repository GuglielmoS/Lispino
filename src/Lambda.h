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

            bool equals(Object *obj) const {
                if (this == obj)
                    return true;
                else if (obj->isLambda()) {
                    Lambda *lambda = static_cast<Lambda*>(obj);

                    if (!lambda->body->equals(body))
                        return false;

                    if (lambda->arguments.size() != arguments.size())
                        return false;

                    for (unsigned int i = 0; i < arguments.size(); i++) {
                        if (arguments[i] != lambda->arguments[i])
                            return false;
                    }
                    
                    return true;
                } else
                    return false;
            } 

            void setBody(Object* body) {
                this->body = body;
            }

            void setArguments(std::vector<std::string> arguments) {
                this->arguments = arguments;
            }

            std::vector<std::string>& getArguments() {
                return arguments;
            }

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

#endif // __LAMBDA_H__
