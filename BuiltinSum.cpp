#include "BuiltinSum.h"

LObject* BuiltinSum::apply(vector<LObject*>& operands) {
    double result = 0.0;
    bool allInteger = true;

    for (unsigned int i = 0; i < operands.size(); i++) {
        if (not operands[i]->isAtom()) {
            cout << "[ILLEGAL] non-numeric value found!" << endl;
            return LNilObject::getNIL();
        }
        else {
            LAtom *curArg = dynamic_cast<LAtom*>(operands[i]);

            if (curArg->isDouble()) {
                result += dynamic_cast<LDouble*>(curArg)->getValue();                            
                allInteger = false;
            }
            else if (not curArg->isInteger()) { 
                cout << "[ILLEGAL] " << curArg->getAtomType() << " found!" << endl;
                return LNilObject::getNIL();
            }
            else {
                result += dynamic_cast<LInteger*>(curArg)->getValue();            
            }
        }
    }

    if (allInteger)
        return new LInteger(static_cast<int>(result));
    else
        return new LDouble(result);
}

