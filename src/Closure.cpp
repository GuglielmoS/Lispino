#include "Closure.h"
#include "VM.h"

using namespace Lispino;

Object* Closure::apply(std::vector<Object*> actualArgs) {
    std::vector<std::string> formalArgs = lambda->getArguments();
    if (formalArgs.size() != actualArgs.size())
        throw std::runtime_error("Invalid function call, wrong number of arguments");

    /*
    std::cout << std::endl;
    std::cout << "CLOSURE APPLICATION:" << std::endl;
    std::cout << "  ARGUMENTS: ";
    for (unsigned int i = 0; i < formalArgs.size(); i++)
        std::cout << formalArgs[i] << " = " << actualArgs[i]->toString() << ", ";
    std::cout << std::endl;
    */

    for (unsigned int i = 0; i < formalArgs.size(); i++)
        env->put(VM::getAllocator().createSymbol(formalArgs[i]), actualArgs[i]);

    /*
    if (env->getParentEnv() != nullptr)
        std::cout << "  ENCLOSING ENV: " << env->getParentEnv()->summary() << std::endl;
    std::cout << "  ENV:           " << env->summary() << std::endl;
    std::cout << "  ENV ADDRESS: " << env.get() << std::endl;
    */

    return lambda->getBody()->eval(*env);
}

