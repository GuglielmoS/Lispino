#ifndef __LLAMBDA__

#define __LLAMBDA__

#include <string>
#include <vector>

#include "LObject.h"
#include "LNilObject.h"
#include "LSymbol.h"
#include "LType.h"

using namespace std;

// forward declarations for getting happy the compiler
class Environment;

class LLambda : public LObject {

    // the environment in which the code will be executed
    Environment* env;

    // the arguments required for the execution
    vector<LObject*> args;

    // the code to execute
    LObject *body; 

public:

    LLambda(vector<LObject*>& args, LObject *body, Environment *parentEnv);

    /**
     * Getters
     */
    
    LType getType() const {
        return LAMBDA;
    }

    Environment* getEnv() const {
        return env;
    }

    LObject* getBody() {
        return body;
    }

    vector<LObject*>& getArgs() {
        return args;
    }

    /**
     * Substitutes the values given as arguments in the code defined in the
     * field 'body'. Thus it evaluates and returns the code in the local environment.
     */
    LObject* call(vector<LObject*>& argValues);
    
    string prettyString() const;

    ~LLambda();
};

#endif // __LLAMBDA__
