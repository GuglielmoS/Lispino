#include "LCons.h"

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

