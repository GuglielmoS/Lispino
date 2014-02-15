#include "Cdr.h"
#include "../VM.h"

using namespace Lispino;

Object* BuiltinCdr::apply(std::vector<Object*>& args, Environment& env) {
    if (args.size() != 1)
        throw std::runtime_error("cdr: wrong number of arguments!");

    Object *value = args[0]->eval(env);
    if (!value->isList())
        throw std::runtime_error("cdr: invalid arguments!");

    return static_cast<List*>(value)->getRest();
}
