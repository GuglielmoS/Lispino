#ifndef __GARBAGE_COLLECTOR_H__
#define __GARBAGE_COLLECTOR_H__

#include "Environment.h"

namespace Lispino {

    class GarbageCollector {

        // global environment reference
        Environment &globalEnv;

        void markVisibleObjects(Environment& env) {
            std::map<Symbol*, Object*, SymbolComparator>::iterator iter;

            for (iter = env.lookupTable()->begin(); iter != env.lookupTable()->end(); ++iter) {
                // mark the current key-value pair
                iter->first->mark();
                iter->second->mark();

                // mark the sub-environment if needed
                if (iter->second->isClosure())
                    markVisibleObjects(*static_cast<Closure*>(iter->second)->getEnv());
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
