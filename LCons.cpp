#include "LCons.h"
#include <sstream>

using namespace std;

void LCons::setCar(LObject* obj) {
    first = obj;
}

void LCons::setCdr(LObject* obj) {
    next = obj;
}

bool LCons::isEmpty() const {
    return first == 0;
}

LType LCons::getType() const {
    return CONS;
}

string LCons::prettyStringHelper(bool parentheses) const {
    if (first == 0) {
        return LNilObject().prettyString();
    }
    else {
        stringstream buf;
        
        if (parentheses)
            buf << "(";
        
        buf << first->prettyString();
        
        if (next != 0) {
            if (next->isCons()) {
                buf << " ";
                buf << dynamic_cast<LCons*>(next)->prettyStringHelper(false);
            }
            else {
                buf << " . ";
                buf << next->prettyString();
            }
        }
        
        if (parentheses)
            buf << ")";

        return buf.str();
    }
}

string LCons::prettyString() const {
    return prettyStringHelper();
}

LCons::~LCons() {
    if (first != 0)
        delete first;
    if (next != 0)
        delete next;
}

