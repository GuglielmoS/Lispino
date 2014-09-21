#include "GarbageCollector.h"

#include <algorithm>
#include <string>

#include "Closure.h"

namespace Lispino {

GarbageCollector::GarbageCollector(std::shared_ptr<Environment> env) : global_env(env) {
  /* DO NOTHING */
}

void GarbageCollector::collect() {
  std::vector<Environment*> marked_envs;
  markVisibleObjects(global_env, marked_envs);
}

bool GarbageCollector::alreadyMarked(std::shared_ptr<Environment> env, std::vector<Environment*>& marked_envs) {
  return std::find(marked_envs.begin(), marked_envs.end(), env.get()) != marked_envs.end();
}

void GarbageCollector::markVisibleObjects(std::shared_ptr<Environment> env, std::vector<Environment*>& marked_envs) {
  // mark the given environment objects if needed
  if (!alreadyMarked(env, marked_envs)) {
    marked_envs.push_back(env.get());

    // loop through the environment values
    for (auto& current_pair : env->getLookupTable()) {
      auto current_symbol = current_pair.second.first;
      auto current_object = current_pair.second.second;

      // mark the current key-value pair
      current_symbol->mark();
      current_object->mark();

      // mark the sub-environment if needed
      if (current_object->isClosure())
        markVisibleObjects(static_cast<Closure*>(current_object)->getEnv(), marked_envs);
    }
  }

  // mark the parent environment if it exists
  std::shared_ptr<Environment> parent_env = env->getParent();
  if (parent_env)
    markVisibleObjects(parent_env, marked_envs);
}

}
