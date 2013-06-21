#include "BuiltinDecrement.h"

LObject* BuiltinDecrement::apply(vector<LObject*>& operands) {
    if (operands.size() != 1) {
        cout << "[ILLEGAL] wrong number of arguments!" << endl;
        return LNilObject::getNIL();
    }

    if (not operands[0]->isAtom()) {
        cout << "[ILLEGAL] non-numeric value found!" << endl;
        return LNilObject::getNIL();
    }
    else {
        LAtom *curArg = dynamic_cast<LAtom*>(operands[0]);

        if (curArg->isDouble())
            return new LDouble(dynamic_cast<LDouble*>(curArg)->getValue() - 1.0);
        else if (curArg->isInteger())
            return new LInteger(dynamic_cast<LInteger*>(curArg)->getValue() - 1);
        else { 
            cout << "[ILLEGAL] " << curArg->getAtomType() << " found!" << endl;
            return LNilObject::getNIL();
        }
    }
}
