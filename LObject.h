#ifndef __LOBJECT__

#define __LOBJECT__

#include <iostream>
#include <string>

#include "LType.h"

class LObject {

public:
    
    bool isAtom() const;
    bool isCons() const;
    bool isLambda() const;
    bool isNIL() const;

    virtual LType getType() const = 0;
    virtual std::string prettyString() const = 0;

    friend std::ostream& operator<<(std::ostream& out, LObject* obj);

};

#endif // __LOBJECT__
