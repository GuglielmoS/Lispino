#include "Environment.h"
#include "LLambda.h"

LLambda::LLambda(vector<LObject*>& args, LObject *body, Environment *parentEnv) :
    args(args), body(body) {

    env = new Environment(parentEnv);
}

LObject* LLambda::call(vector<LObject*>& argValues) {
    if (args.size() != argValues.size()) {
        cout << "INVALID NUMBER OF ARGUMENTS!" << endl;
        return LNilObject::getNIL();
    }

    for (unsigned int i = 0; i < argValues.size(); i++) {
        if (args[i]->isAtom()) {
            if (dynamic_cast<LAtom*>(args[i])->isSymbol())
                env->bind(dynamic_cast<LSymbol*>(args[i]), argValues[i]);
        }
        else {
            cout << "NON-ATOM ARGUMENT NAME - INVALID!" << endl;
            cout << "ARG: " << args[i] << endl;
            return LNilObject::getNIL();
        }
    }

    return env->eval(body);
}

string LLambda::prettyString() const {
    return "GENERIC-LAMBDA";
}

LLambda::~LLambda() {
    delete body;
    delete env;
}

