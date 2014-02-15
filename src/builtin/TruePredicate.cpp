#include "TruePredicate.h"
#include "../VM.h"
#include "../Boolean.h"

using namespace Lispino;

Object* BuiltinTruePredicate::apply(std::vector<Object*>& args, Environment& env) {
    if (args.size() != 1)
        throw std::runtime_error("true?: wrong number of arguments!");

    Object *value = args[0]->eval(env);

    if (!value->isBoolean())
        throw std::runtime_error("true?: invalid arguments");

    return VM::getAllocator().createBoolean(static_cast<Boolean*>(value)->isTrue());
}
