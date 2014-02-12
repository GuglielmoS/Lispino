#include "Closure.h"
#include "VM.h"

using namespace Lispino;

Object* Closure::apply(std::vector<Object*>& actualArgs) {
    std::vector<std::string>& formalArgs = lambda->getArguments();

    if (formalArgs.size() != actualArgs.size())
        throw std::runtime_error("Invalid function call, wrong number of arguments");

    for (unsigned int i = 0; i < formalArgs.size(); i++)
        env->put(VM::getAllocator().createSymbol(formalArgs[i]), actualArgs[i]);

    return lambda->getBody()->eval(*env);
}

