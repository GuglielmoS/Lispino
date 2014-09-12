#include "Lambda.h"

#include "VM.h"

namespace Lispino {

    Lambda::Lambda() : body(nullptr) {
        /* DO NOTHING */
    }

    Lambda::Lambda(Object* body, std::vector<std::string> arguments) :
        body(body), arguments(arguments) {
        /* DO NOTHING */
    }

    void Lambda::setBody(Object* body) {
        this->body = body;
    }

    void Lambda::setArguments(std::vector<std::string> arguments) {
        this->arguments = arguments;
    }

    Object* Lambda::getBody() {
        return body;
    }

    std::vector<std::string> Lambda::getArguments() {
        return arguments;
    }

    Object* Lambda::eval(Environment& env) {
        return VM::getAllocator().createClosure(this, &env);
    }

    void Lambda::mark() {
        Object::mark();
        body->mark();
    }

    bool Lambda::isLambda() const {
        return true;
    }

    std::string Lambda::toString() const {
        return "LAMBDA";
    }
}
