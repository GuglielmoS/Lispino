#include "Add.h"

#include "../VM.h"

namespace Lispino {
    Object* BuiltinAdd::apply(std::vector<Object*>& args, Environment& env) {
        if (args.size() == 0)
            throw std::runtime_error("+: wrong number of arguments!");

        Object* result = args[0]->eval(env);
        for (unsigned int i = 1; i < args.size(); i++)
            result = result->add(args[i]->eval(env));

        return result;
    }
}
