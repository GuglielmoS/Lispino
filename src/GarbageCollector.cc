#include "GarbageCollector.h"

#include <string>

#include "Closure.h"

namespace Lispino {

    GarbageCollector::GarbageCollector(Environment& env) : globalEnv(env) {
        /* DO NOTHING */
    }

    void GarbageCollector::collect() {
        std::vector<Environment*> markedEnvs;
        markVisibleObjects(&globalEnv, markedEnvs);
    }

    bool GarbageCollector::alreadyMarked(Environment* env, std::vector<Environment*> markedEnvs) {
        for (size_t i = 0; i < markedEnvs.size(); i++) {
            if (markedEnvs[i] == env) {
                return true;
            }
        }

        return false;
    }

    void GarbageCollector::markVisibleObjects(Environment* env, std::vector<Environment*>& markedEnvs) {
        // mark the given environment objects if needed
        if (!alreadyMarked(env, markedEnvs)) {
            markedEnvs.push_back(env);
            for (auto iter = env->lookupTable().begin(); iter != env->lookupTable().end(); ++iter) {
                // mark the current key-value pair
                (iter->second).first->mark();
                (iter->second).second->mark();

                // mark the sub-environment if needed
                if ((iter->second).second->isClosure()) {
                    markVisibleObjects(static_cast<Closure*>((iter->second).second)->getEnv(), markedEnvs);
                }
            }

            // mark the parent environment if it exists
            Environment *parentEnv = env->getParent();
            if (parentEnv != nullptr) {
                markVisibleObjects(parentEnv, markedEnvs);
            }
        }
    }
}
