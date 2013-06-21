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

    string prettyStringHelper(bool parentheses = true) const;
    string prettyString() const;
    ~LCons();

};

#endif // __LCONS__
