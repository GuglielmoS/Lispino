#include "FalsePredicate.h"
#include "../VM.h"
#include "../Boolean.h"

using namespace Lispino;

Object* BuiltinFalsePredicate::apply(std::vector<Object*>& args, Environment& env) {
    if (args.size() != 1)
        throw std::runtime_error("false?: wrong number of arguments!");

    Object *value = args[0]->eval(env);

    if (!value->isBoolean())
        throw std::runtime_error("false?: invalid arguments");

    return VM::getAllocator().createBoolean(static_cast<Boolean*>(value)->isFalse());
}
