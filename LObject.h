#ifndef __LOBJECT__

#define __LOBJECT__

#include <iostream>
#include <string>

#include "LType.h"

using namespace std;

class LObject {

public:
    
    bool isAtom() const {
        return getType() == ATOM;
    }

    bool isCons() const {
        return getType() == CONS;
    }

    bool isLambda() const {
        return getType() == LAMBDA;
    }

    bool isNIL() const {
        return getType() == NIL;
    }

    virtual LType getType() const = 0;
    virtual string prettyString() const = 0;    

    friend ostream& operator<<(ostream& out, LObject* obj) {
        out << obj->prettyString();
        return out;
    }

};

#endif // __LOBJECT__
