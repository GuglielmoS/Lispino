#ifndef __LCONS__

#define __LCONS__

#include <sstream>
#include <string>

#include "LObject.h"
#include "LNilObject.h"
#include "LType.h"

using namespace std;

class LCons : public LObject {
    
    LObject *first;
    LObject *next;
    
public:
    
    LCons() : first(0), next(0) {}
    LCons(LObject* first) : first(first), next(0) {}
    LCons(LObject* first, LObject* second) :
        first(first), next(second) {}
    
    friend LObject* car(const LCons* obj) {
        return (obj != 0 && obj->first != 0) ? obj->first : LNilObject::getNIL();
    }

    friend LObject* cdr(const LCons* obj) {
        return (obj != 0 && obj->next != 0) ? obj->next : LNilObject::getNIL();
    }

    void setCar(LObject* obj) {
        first = obj;
    }

    void setCdr(LObject* obj) {
        next = obj;
    }

    bool isEmpty() const {
        return first == 0;
    }

    LType getType() const {
        return CONS;
    }

    string prettyStringHelper(bool parentheses = true) const {
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

    string prettyString() const {
        return prettyStringHelper();
    }

    ~LCons() {
        if (first != 0)
            delete first;
        if (next != 0)
            delete next;
    }
};

#endif // __LCONS__
