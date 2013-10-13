#ifndef __LNILOBJECT_H__
#define __LNILOBJECT_H__

// c++
#include <string>

// lisp objects 
#include "LObject.h"

// exceptions
#include "EvalException.h"

class LNilObject : public LObject {

public:

    static LNilObject* getNIL() {
        static LNilObject obj;

        return &obj;
    }

    LType getType() const {
        return NIL;
    }

    std::string prettyString() const {
        return "NIL";
    }

    LObject* eval(Environment& env) throw (EvalException) {
        return LNilObject::getNIL();
    }
};

#endif // __LNILOBJECT_H__
