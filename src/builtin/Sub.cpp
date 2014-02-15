#include "Sub.h"
#include "../VM.h"

using namespace Lispino;

Object* BuiltinSub::apply(std::vector<Object*>& args, Environment& env) {
    if (args.size() <= 1)
        throw std::runtime_error("-: wrong number of arguments!");

    Object* result = args[0]->eval(env);
    for (unsigned int i = 1; i < args.size(); i++)
        result = result->sub(args[i]->eval(env));

    return result;
}

