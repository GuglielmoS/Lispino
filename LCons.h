#ifndef __LCONS__

#define __LCONS__

#include <string>

#include "LObject.h"
#include "LNilObject.h"
#include "LType.h"

class LCons : public LObject {
    
    LObject *first;
    LObject *next;
    
public:
    
    LCons() : first(0), next(0) {}
    LCons(LObject* first) : first(first), next(0) {}
    LCons(LObject* first, LObject* second) :
        first(first), next(second) {}
    
    void setCar(LObject *obj);
    void setCdr(LObject *obj);
    LType getType() const;
    bool isEmpty() const;

    std::string prettyStringHelper(bool parentheses = true) const;
    std::string prettyString() const;
    ~LCons();
    
    friend LObject* car(const LCons *obj) {
        return (obj != 0 && obj->first != 0) ? obj->first : LNilObject::getNIL();
    }

    friend LObject* cdr(const LCons *obj) {
        return (obj != 0 && obj->next != 0) ? obj->next : LNilObject::getNIL();
    }

};

#endif // __LCONS__
