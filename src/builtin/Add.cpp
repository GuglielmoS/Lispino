#include "Add.h"
#include "../VM.h"

using namespace Lispino;

Object* BuiltinAdd::apply(std::vector<Object*>& args) {
    if (args.size() <= 1)
        throw std::runtime_error("+: wrong number of arguments!");

    Object* result = args[0];
    for (unsigned int i = 1; i < args.size(); i++)
        result = result->add(args[i]);

    return result;
}

