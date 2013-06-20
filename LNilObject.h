#ifndef __LNILOBJECT__

#define __LNILOBJECT__

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

#endif // __LNILOBJECT__
