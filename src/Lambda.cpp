#include "Lambda.h"
#include "VM.h"

using namespace Lispino;

Object* Lambda::eval(Environment& env) {
    return VM::getAllocator().createClosure(this, &env);
}
