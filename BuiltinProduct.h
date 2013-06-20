#ifndef __BUILTIN_PRODUCT__

#define __BUILTIN_PRODUCT__

#include <vector>

#include "LObject.h"
#include "LNilObject.h"
#include "LInteger.h"
#include "LDouble.h"
#include "LSymbol.h"
#include "BuiltinFunction.h"

using namespace std;

class BuiltinProduct : public BuiltinFunction {
    
public:

    BuiltinProduct(const string& name) : BuiltinFunction(name) {}
    
    LObject* apply(vector<LObject*>& operands) {
        double result = 1.0;
        bool allInteger = true;

        for (unsigned int i = 0; i < operands.size(); i++) {
            if (not operands[i]->isAtom()) {
                cout << "[ILLEGAL] non-numeric value found!" << endl;
                return LNilObject::getNIL();
            }
            else {
                LAtom *curArg = dynamic_cast<LAtom*>(operands[i]);

                if (curArg->isDouble()) {
                    result *= dynamic_cast<LDouble*>(curArg)->getValue();                            
                    allInteger = false;
                }
                else if (not curArg->isInteger()) { 
                    cout << "[ILLEGAL] " << curArg->getAtomType() << " found!" << endl;
                    return LNilObject::getNIL();
                }
                else {
                    result *= dynamic_cast<LInteger*>(curArg)->getValue();            
                }
            }
        }

        if (allInteger)
            return new LInteger(static_cast<int>(result));
        else
            return new LDouble(result);
    }

};

#endif // __BUILTIN_PRODUCT__

