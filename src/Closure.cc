#include "Closure.h"
#include "VM.h"

namespace Lispino {

    Closure::Closure() : lambda(nullptr), env(nullptr) {
        /* DO NOTHING */
    }

    Closure::Closure(Lambda *lambda, Environment *parentEnv) : 
        lambda(lambda), env(new Environment(parentEnv)) {
        /* DO NOTHING */    
    }

    Object* Closure::eval(Environment& env) {
        return this;
    }

    Object* Closure::apply(std::vector<Object*>& actualArgs) {
        std::vector<std::string> formalArgs = lambda->getArguments();

        if (formalArgs.size() != actualArgs.size())
            throw std::runtime_error("Invalid function call, wrong number of arguments");

        for (unsigned int i = 0; i < formalArgs.size(); i++)
            env->put(VM::getAllocator().createSymbol(formalArgs[i]), actualArgs[i]);

        return lambda->getBody()->eval(*env);
    }
 
    void Closure::setLambda(Lambda *lambda) {
        this->lambda = lambda;
    }

    void Closure::setEnv(Environment *parentEnv) {
        this->env.reset(new Environment(parentEnv));
    }

    Environment* Closure::getEnv() {
        return env.get();
    }

    void Closure::mark() {
        Object::mark();
        lambda->mark();
    }

    bool Closure::isClosure() const {
        return true;
    }

    std::string Closure::toString() const {
        return "CLOSURE";
    }
}
