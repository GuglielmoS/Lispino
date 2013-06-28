#ifndef __LNIL_OBJECT__

#define __LNIL_OBJECT__

#include <string>

#include "LObject.h"
#include "LType.h"

class LNilObject : public LObject {

public:

    LType getType() const;
    std::string prettyString() const;

    static LNilObject* getNIL() {
        static LNilObject obj;

        return &obj;
    }

};

#endif // __LNIL_OBJECT__
