#include "Cons.h"

#include "../VM.h"

namespace Lispino {
    namespace Builtins {
        Object* Cons::apply(std::vector<Object*>& args, Environment& env) {
            if (args.size() != 2)
                throw std::runtime_error("cons: wrong number of arguments!");

            return VM::getAllocator().createList(args[0]->eval(env), args[1]->eval(env));
        }
    }
}
