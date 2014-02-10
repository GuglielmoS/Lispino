#include "Object.h"
#include "VM.h"

using namespace Lispino;

Object* Object::eval() {
    return eval(VM::getGlobalEnv());
}

void Object::mark() {
    markFlag = true;
}

void Object::unmark() {
    markFlag = false;
}

bool Object::isMarked() const {
    return markFlag;
}
