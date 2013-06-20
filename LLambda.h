#ifndef __LLAMBDA__

#define __LLAMBDA__

#include <string>
#include <vector>

#include "LObject.h"
#include "LNilObject.h"
#include "LSymbol.h"
#include "LType.h"

using namespace std;

class Environment;

class LLambda : public LObject {

    vector<LObject*> args;
    LObject *body; 
    Environment* env;

public:
    
    LLambda(vector<LObject*>& args, LObject *body, Environment *parentEnv);
    LObject* call(vector<LObject*>& argValues);
    LType getType() const;
    Environment* getEnv();
    LObject* getBody();
    vector<LObject*>& getArgs();
    string prettyString() const;
    ~LLambda();
};

#endif // __LLAMBDA__
