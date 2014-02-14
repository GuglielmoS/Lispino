#ifndef __GARBAGE_COLLECTOR_H__
#define __GARBAGE_COLLECTOR_H__

#include "Environment.h"

namespace Lispino {

    class GarbageCollector {

        // global environment reference
        Environment &globalEnv;

        void markVisibleObjects(Environment& env) {
            std::unordered_map<std::string, std::pair<Symbol*, Object*>>::iterator iter;

            for (iter = env.lookupTable().begin(); iter != env.lookupTable().end(); ++iter) {
                // mark the current key-value pair
                (iter->second).first->mark();
                (iter->second).second->mark();

                // mark the sub-environment if needed
                if ((iter->second).second->isClosure())
                    markVisibleObjects(*static_cast<Closure*>((iter->second).second)->getEnv());
            }
        }

        public:

            GarbageCollector(Environment& env) : globalEnv(env) {}

            void collect() {
                markVisibleObjects(globalEnv);
            }

    };
};

#endif // __GARBAGE_COLLECTOR_H__
