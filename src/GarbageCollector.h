#ifndef __GARBAGE_COLLECTOR_H__
#define __GARBAGE_COLLECTOR_H__

#include "Environment.h"

namespace Lispino {

    class GarbageCollector {

        // global environment reference
        Environment &globalEnv;

        bool alreadyMarked(Environment* env, std::vector<Environment*> markedEnvs) {
            for (size_t i = 0; i < markedEnvs.size(); i++) {
                if (markedEnvs[i] == env) {
                    return true;
                }
            }

            return false;
        }

        void markVisibleObjects(Environment* env, std::vector<Environment*>& markedEnvs, int level = 0) {
            if (!alreadyMarked(env, markedEnvs)) {
                std::unordered_map<std::string, std::pair<Symbol*, Object*>>::iterator iter;

                // mark the current env
                markedEnvs.push_back(env);
                for (iter = env->lookupTable().begin(); iter != env->lookupTable().end(); ++iter) {
                    // mark the current key-value pair
                    (iter->second).first->mark();
                    (iter->second).second->mark();

                    // mark the sub-environment if needed
                    if ((iter->second).second->isClosure()) {
                        markVisibleObjects(static_cast<Closure*>((iter->second).second)->getEnv(), markedEnvs, level+1);
                    }
                }

                // mark the parent env if it exists
                Environment *parentEnv = env->getParent();
                if (parentEnv != nullptr) {
                    markVisibleObjects(parentEnv, markedEnvs, level+1);
                }
            }
        }

        public:

            GarbageCollector(Environment& env) : globalEnv(env) {}

            void collect() {
                std::vector<Environment*> markedEnvs;
                markVisibleObjects(&globalEnv, markedEnvs);
            }
    };
};

#endif // __GARBAGE_COLLECTOR_H__
