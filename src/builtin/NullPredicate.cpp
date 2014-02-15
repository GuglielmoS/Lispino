#include "NullPredicate.h"
#include "../VM.h"

using namespace Lispino;

Object* BuiltinNullPredicate::apply(std::vector<Object*>& args, Environment& env) {
    if (args.size() != 1)
        throw std::runtime_error("null?: wrong number of arguments!");

    return VM::getAllocator().createBoolean(args[0]->eval(env)->isNil());
}

