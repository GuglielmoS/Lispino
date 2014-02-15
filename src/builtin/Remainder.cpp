#include "Remainder.h"
#include "../VM.h"

using namespace Lispino;

Object* BuiltinRemainder::apply(std::vector<Object*>& args) {
    if (args.size() <= 1)
        throw std::runtime_error("remainder: wrong number of arguments!");

    Object* result = args[0];
    for (unsigned int i = 1; i < args.size(); i++)
        result = result->remainder(args[i]);

    return result;
}

