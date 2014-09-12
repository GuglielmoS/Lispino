#include "Nil.h"

namespace Lispino {
    Object* Nil::eval(Environment& env) {
        return this;
    }

    int Nil::compare(Object* obj) {
        return obj->compareNil(this);
    }

    int Nil::compareNil(Nil* obj) {
        return 0;
    }

    int Nil::compareList(List* obj) {
        return -1;
    }

    int Nil::compareInt(IntNumber* obj) {
        return -1;
    }

    int Nil::compareFloat(FloatNumber* obj) {
        return -1;
    }

    int Nil::compareSymbol(Symbol* obj) {
        return -1;
    }

    int Nil::compareString(String* obj) {
        return -1;
    }

    int Nil::compareBoolean(Boolean* obj) {
        return -1;
    }

    int Nil::compareSequence(Sequence* obj) {
        return -1;
    }

    bool Nil::isNil() const {
        return true;
    }

    std::string Nil::toString() const {
        return "NIL";
    }
}
