#include "LowerThan.h"
#include "../VM.h"

using namespace Lispino;

Object* BuiltinLowerThan::apply(std::vector<Object*>& args) {
    if (args.size() <= 1)
        throw std::runtime_error("<: wrong number of arguments");

    for (unsigned int i = 0; i < args.size()-1; i++) {
        if (args[i]->compare(args[i+1]) >= 0)
            return VM::getAllocator().createBoolean(false);
    }

    return VM::getAllocator().createBoolean(true);
}

