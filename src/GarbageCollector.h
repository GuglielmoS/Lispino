#ifndef LISPINO_GARBAGECOLLECTOR_H_
#define LISPINO_GARBAGECOLLECTOR_H_

#include <vector>

#include "Environment.h"

namespace Lispino {

    class GarbageCollector {

        // global environment reference
        Environment &globalEnv;

        bool alreadyMarked(Environment* env, std::vector<Environment*> markedEnvs);
        void markVisibleObjects(Environment* env, std::vector<Environment*>& markedEnvs);

        public:

            GarbageCollector(Environment& env);

            void collect();
    };
};

#endif // LISPINO_GARBAGECOLLECTOR_H_
