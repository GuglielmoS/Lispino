#include "Symbol.h"
#include "Environment.h"

using namespace Lispino;

Object* Symbol::eval(Environment& env) {
    return env.get(this);
}
