#include "Car.h"
#include "../VM.h"

using namespace Lispino;

Object* BuiltinCar::apply(std::vector<Object*>& args, Environment& env) {
    if (args.size() != 1)
        throw std::runtime_error("car: wrong number of arguments!");

    Object *value = args[0]->eval(env);
    if (!value->isList())
        throw std::runtime_error("car: invalid arguments!");

    return static_cast<List*>(value)->getFirst();
}
