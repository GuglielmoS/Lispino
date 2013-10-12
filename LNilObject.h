#ifndef __LNIL_OBJECT__

#define __LNIL_OBJECT__

#include <string>

#include "LObject.h"
#include "LType.h"

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

    LObject* clone() const {
        return LNilObject::getNIL();
    }

    std::string prettyString() const {
        return "NIL";
    }

    LObject* eval(Environment& env) throw (EvalException) {
        return LNilObject::getNIL();
    }

    //~LNilObject() {}
};

#endif // __LNIL_OBJECT__
