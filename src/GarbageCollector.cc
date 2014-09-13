#include "GarbageCollector.h"

#include <string>

#include "Closure.h"

namespace Lispino {

GarbageCollector::GarbageCollector(Environment& env) : global_env(env) {
  /* DO NOTHING */
}

void GarbageCollector::collect() {
  std::vector<Environment*> markedEnvs;
  markVisibleObjects(&global_env, markedEnvs);
}

bool GarbageCollector::alreadyMarked(Environment* env, std::vector<Environment*> marked_envs) {
  for (size_t i = 0; i < marked_envs.size(); i++) {
    if (marked_envs[i] == env)
      return true;
  }

  return false;
}

void GarbageCollector::markVisibleObjects(Environment* env, std::vector<Environment*>& marked_envs) {
  // mark the given environment objects if needed
  if (!alreadyMarked(env, marked_envs)) {
    marked_envs.push_back(env);
    auto lookup_table = env->lookupTable();
    for (auto iter = lookup_table.begin(); iter != lookup_table.end(); ++iter) {
      // mark the current key-value pair
      (iter->second).first->mark();
      (iter->second).second->mark();

      // mark the sub-environment if needed
      if ((iter->second).second->isClosure())
        markVisibleObjects(static_cast<Closure*>((iter->second).second)->getEnv(), marked_envs);
    }

    // mark the parent environment if it exists
    Environment *parentEnv = env->getParent();
    if (parentEnv != nullptr)
      markVisibleObjects(parentEnv, marked_envs);
  }
}

}
