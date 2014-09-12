#include "Lambda.h"

#include "VM.h"

namespace Lispino {
    Object* Lambda::eval(Environment& env) {
        return VM::getAllocator().createClosure(this, &env);
    }

    void Lambda::setArguments(std::vector<std::string> arguments) {
        this->arguments = arguments;
    }

    std::vector<std::string> Lambda::getArguments() {
        return arguments;
    }
}
