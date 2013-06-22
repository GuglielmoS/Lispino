#include "BuiltinCdr.h"

LObject* BuiltinCdr::apply(vector<LObject*>& operands) {
    if (operands.size() != 1) {
        cout << "[ILLEGAL] wrong number of arguments!" << endl;
        return LNilObject::getNIL();
    }
    
    LObject* arg = operands.front();

    if (arg->isCons())
        return cdr(dynamic_cast<LCons*>(arg));

    cout << "[ILLEGAL] wrong argument's type!" << endl;
    return LNilObject::getNIL();
}


