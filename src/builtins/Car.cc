#include "Car.h"

#include "../VM.h"

namespace Lispino {
    namespace Builtins {
        Object* Car::apply(std::vector<Object*>& args, Environment& env) {
            if (args.size() != 1)
                throw std::runtime_error("car: wrong number of arguments!");

            Object *value = args[0]->eval(env);
            if (!value->isList())
                throw std::runtime_error("car: invalid arguments!");

            return static_cast<List*>(value)->getFirst();
        }
    }
}
