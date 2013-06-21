#ifndef __LNIL_OBJECT__

#define __LNIL_OBJECT__

#include <string>

#include "LObject.h"
#include "LType.h"

class LNilObject : public LObject {

public:

    static LNilObject* getNIL() {
        static LNilObject obj;

        return &obj;
    }

    LType getType() const {
        return NIL;
    }

    string prettyString() const {
        return "NIL";
    }

};

#endif // __LNIL_OBJECT__
